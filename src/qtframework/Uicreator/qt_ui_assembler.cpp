#include "qt_ui_assembler.h"
#include <QtGui>
#include <QtWidgets>
#include <QtCore/QObject>
#include <QtOpenGL/QGLWidget>
#include <QtQuick>
#include "Uicreator/xml_ui_paser.h"
#include "Uicreator/event_handler.h"
#include "Uicreator/ui_node.h"
#include "Utils/variant.h"
#include "Res/R.h"
#include "UIs/sl_Button.h"
#include "UIs/sl_MutexButtonBox.h"
#include "UIs/sl_ImageWidget.h"
#include "UIs/sl_AnimationWidget.h"
#include "UIs/TitleBar.h"
#include "Utils/qt_standard.h"
#include "Utils/util.h"
#include "Utils/Log.h"
#include "UIs/sl_VectorContainer.h"
#include "UIs/sl_MapContainer.h"
#include "UIs/sl_ToolPanel.h"
#ifdef USE_QCUSTOM_PLOT
#include <QCustomPlot.h>
#endif
#include <string.h>

Q_DECLARE_METATYPE(ui_node*) //��qtʶ��ui_node����
//���캯��
//������root �ڵ����ĸ��ڵ�
//����ֵ����
qt_ui_assembler::qt_ui_assembler(ui_node* root)
	:_root(root)
{
	//_event_handler = new event_handler(NULL);
	//���ｫevent_handler��ָ��ȫ��Ψһһ��
	_event_handler = &gs_event_handler;
}
//���캯��
//������parser ������ָ��
//����ֵ����
qt_ui_assembler::qt_ui_assembler(xml_ui_paser* parser)
	:_parser(parser)
{
	_root = (ui_node*)_parser->getRoot();
	//_event_handler = new event_handler(NULL);
	_event_handler = &gs_event_handler;
}
//��������
//��������
//����ֵ����
qt_ui_assembler::~qt_ui_assembler(void)
{
	//_root->release(); ����root����new�ģ�����parser���ͷ� //20150925
	/*if (_event_handler!=NULL)  
	{
		delete _event_handler;
		_event_handler = NULL;
	}*/
}

//��ø��ڵ������objectָ��
//��������
//����ֵ�����ڵ��������
void* qt_ui_assembler::getRootObject()
{
	return _root->getObject();
}
//����¼�������
//��������
//����ֵ���¼�������ָ��
void* qt_ui_assembler::getEventHandler()
{
	return _event_handler;
}
//��ø��ڵ�����
//��������
//����ֵ���ڵ�����
ui_node::NodeType qt_ui_assembler::getRootType()
{
	ui_node::NodeType type = _root->getType();
	return _root->getType();
}
//��װ
//��������
//����ֵ����
void qt_ui_assembler::assemble()
{
	parseUITree(_root);
}
//�����ڵ���
//������node ���ڵ�ָ��
//����ֵ����
void qt_ui_assembler::parseUITree(ui_node* node)
{
	createUI(node);
	if (node->getChildNum() != 0)
	{
		for(int i=0; i < node->getChildNum(); i++)
		{
			ui_node* child_node = (ui_node*)node->getChild(i);
			//child_node->setParent(node); //���ýڵ�ĸ��ڵ�
			if (child_node)
			{
				createUI(child_node);
				//�жϸ��ڵ���ӽڵ��Ƿ���Ч
				if ((child_node->getObject())&&(node->getObject()))
				{
					assembleNodes(node,child_node);
					parseUITree(child_node);
				}	
			}		
		}
	}
	else
	{
		return;
	}
}
//װ���ӽڵ�͸��ڵ�
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleNodes(ui_node* father,ui_node* child)
{
	
	//װ���ӽڵ�͸��ڵ�
	switch (father->getType())
	{
	case ui_node::LAYOUT:
		{
			assembleLayoutAndWidgetOrLayout(father,child);
		}
		break;
	case ui_node::WIDGET:
		{
			if(child->getType()==ui_node::LAYOUT)
			{
				assembleWidgetAndLayout(father,child);
			}
			else if (child->getType()==ui_node::WIDGET)
			{
				assembleWidgetAndWidget(father,child);
			}
			else if (child->getType()==ui_node::ITEM)
			{
				assembleWidgetAndItem(father,child);
			}
			else if (child->getType()==ui_node::ITEMS)
			{
				assembleWidgetAndItems(father,child);
			}
		}
		break;
	case ui_node::CONTAINER:
		{
			assembleContainerAndWidget(father,child);
		}
		break;
	case ui_node::ITEM:
		{
			if (strcmp(father->getName(),"Action")==0)
			{
				QAction* action = (QAction*)father->getObject();
				if (strcmp(child->getName(),"Menu")==0)
				{
					QMenu* menu = (QMenu*)child->getObject();
					action->setMenu(menu);
				}
			}
		}
		break;
	default:
		break;
	}
}
//װ��Layout��Widget����Layout��Layout
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleLayoutAndWidgetOrLayout(ui_node* father,ui_node* child)
{
	if(strcmp(father->getName(),"VLayout")==0||strcmp(father->getName(),"HLayout")==0)
	{
		QBoxLayout* layout = (QBoxLayout*)father->getObject();
		if (child->getType()==ui_node::LAYOUT)
		{
			QLayout* child_layout = (QLayout*)child->getObject();
			if (child->hasAttribute("stretch"))
			{
				layout->addLayout(child_layout,STR_TO_INT(child->getAttribute("stretch")));
			}else
			{
				layout->addLayout(child_layout);
			}
			if (child->hasAttribute("align"))
			{
				layout->setAlignment(child_layout,qt_standard::getAlignment(child->getAttribute("align")));
			}

		}
		else if (child->getType()==ui_node::WIDGET)
		{
			QWidget* child_widget =(QWidget*)child->getObject();
			if (child->hasAttribute("stretch"))
			{
				layout->addWidget(child_widget,STR_TO_INT(child->getAttribute("stretch")));
			}else
			{
				layout->addWidget(child_widget);
			}
			if (child->hasAttribute("align"))
			{
				layout->setAlignment(child_widget,qt_standard::getAlignment(child->getAttribute("align")));
			}
		}
		else if (child->getType()==ui_node::ITEM)
		{
			if (strcmp(child->getName(),"Spacing")==0&&child->hasAttribute("size"))
			{
				layout->addSpacing(STR_TO_INT(child->getAttribute("size")));
			}
			if (strcmp(child->getName(),"Stretch")==0&&child->hasAttribute("size"))
			{
				layout->addStretch(STR_TO_INT(child->getAttribute("size")));
			}
		}
	}
	else if (strcmp(father->getName(),"GridLayout")==0)
	{
		QGridLayout* layout = (QGridLayout*)father->getObject();
		if (child->hasAttribute("row")&&child->hasAttribute("col"))
		{
			int r = STR_TO_INT(child->getAttribute("row"));
			int c = STR_TO_INT(child->getAttribute("col"));
			int rs = child->hasAttribute("rowSpan")?STR_TO_INT(child->getAttribute("rowSpan")):1;
			int cs = child->hasAttribute("colSpan")?STR_TO_INT(child->getAttribute("colSpan")):1;
			Qt::Alignment align = child->hasAttribute("align")?qt_standard::getAlignment(child->getAttribute("align")):(Qt::Alignment)0;
			bool colEqual = father->hasAttribute("colEqual")?STR_TO_BOOL(father->getAttribute("colEqual")):false; //�ж��ǲ���ÿһ�п����ͬ
			if (child->getType()==ui_node::WIDGET)
			{
				QWidget* child_widget = (QWidget*)child->getObject();
				layout->addWidget(child_widget,r,c,rs,cs,align);
			}
			else if (child->getType()==ui_node::LAYOUT)
			{
				QLayout* child_layout = (QLayout*)child->getObject();
				layout->addLayout(child_layout,r,c,rs,cs,align);
			}
			if (colEqual)
			{
				layout->setColumnStretch(c,1);
			}	
		}
	}
	else if (strcmp(father->getName(),"StackedLayout")==0)
	{
		QStackedLayout* layout = (QStackedLayout*)father->getObject();
		if (child->getType()==ui_node::WIDGET)
		{
			QWidget* child_widget = (QWidget*)child->getObject();
			if (child->hasAttribute("index"))
			{
				int i = STR_TO_INT(child->getAttribute("index"));
				layout->insertWidget(i,child_widget);
				if (father->hasAttribute("initIndex"))
				{
					int j = STR_TO_INT(father->getAttribute("initIndex"));
					if (i==j)
					{
						layout->setCurrentIndex(j);
					}	
				}

			}else
			{
				layout->addWidget(child_widget);
			}
		}	
	}
	else if (strcmp(father->getName(),"TableLayout")==0)
	{
		QGridLayout* layout = (QGridLayout*)father->getObject();
		if (child->hasAttribute("row"))
		{
			int row = STR_TO_INT(child->getAttribute("row"));
			int num = child->getChildNum();
			for (int i=0;i<num;i++)
			{
				ui_node* temp = child->getChild(i);
				createUI(temp);
				if (temp->getType()==ui_node::WIDGET)
				{
					Qt::Alignment align = temp->hasAttribute("align")?qt_standard::getAlignment(temp->getAttribute("align")):(Qt::Alignment)0;
					QWidget* temp_widget = (QWidget*)temp->getObject();
					layout->addWidget(temp_widget,row,i,align);
				}
				else if (temp->getType()==ui_node::LAYOUT)
				{
					Qt::Alignment align = temp->hasAttribute("align")?qt_standard::getAlignment(temp->getAttribute("align")):(Qt::Alignment)0;
					QLayout* temp_layout = (QLayout*)temp->getObject();
					layout->addLayout(temp_layout,row,i,align)		;
				}
			}
		}
	}	
}
//װ��Widget��Layout
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndLayout(ui_node* father,ui_node* child)
{
	QWidget* widget = (QWidget*)father->getObject();
	QLayout* child_layout = (QLayout*)child->getObject();
	widget->setLayout(child_layout);
	if (strcmp(father->getName(),"VSplitter")==0||strcmp(father->getName(),"HSplitter")==0)
	{
		QSplitter* widget = (QSplitter*)father->getObject();
		QWidget* temp_widget = new QWidget;
		temp_widget->setContentsMargins(0,0,0,0);
		QLayout* child_layout = (QLayout*)child->getObject();
		temp_widget->setLayout(child_layout);
		widget->addWidget(temp_widget);
	}
}
//װ��Widget��Widget
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndWidget(ui_node* father,ui_node* child)
{
	QWidget* child_widget = (QWidget*)child->getObject();
	if (strcmp(father->getName(),"Tabs")==0)
	{
		QTabWidget* widget = (QTabWidget*)father->getObject();
		if (child->hasAttribute("index"))
		{
			int i = STR_TO_INT(child->getAttribute("index"));
			if (child->hasAttribute("icon"))
			{
				std::string url;
				getResImageOrIconUrl(url,child->getAttribute("icon"));
				QIcon icon(url.c_str());
				widget->insertTab(i,child_widget,icon,child->getAttribute("text"));
			}
			else
			{
				widget->insertTab(i,child_widget,child->getAttribute("text"));
			}
			if (father->hasAttribute("initIndex"))
			{
				int j = STR_TO_INT(father->getAttribute("initIndex"));
				if (i==j)
				{
					widget->setCurrentIndex(j);
				}	
			}

		}else
		{
			if (child->hasAttribute("icon"))
			{
				std::string url;
				getResImageOrIconUrl(url,child->getAttribute("icon"));
				QIcon icon(url.c_str());
				widget->addTab(child_widget,icon,child->getAttribute("text"));
			}
			else
			{
				widget->addTab(child_widget,child->getAttribute("text"));
			}
		}
	}
	else if (strcmp(father->getName(),"Tab")==0)
	{
		QWidget* widget = (QWidget*)father->getObject();
		widget->setContentsMargins(0,0,0,0);
		QVBoxLayout* temp_layout = new QVBoxLayout;
		temp_layout->setContentsMargins(0,0,0,0);
		temp_layout->addWidget(child_widget);
		widget->setLayout(temp_layout);
	}
	else if (strcmp(father->getName(),"VSplitter")==0||strcmp(father->getName(),"HSplitter")==0)
	{
		QSplitter* widget = (QSplitter*)father->getObject();
		widget->addWidget(child_widget);
	}
	else if (strcmp(father->getName(),"StackedWidget")==0)
	{
		QStackedWidget* widget = (QStackedWidget*)father->getObject();
		if (child->hasAttribute("index"))
		{
			int i = STR_TO_INT(child->getAttribute("index"));
			widget->insertWidget(i,child_widget);
			if (father->hasAttribute("initIndex"))
			{
				int j = STR_TO_INT(father->getAttribute("initIndex"));
				if (i==j)
				{
					widget->setCurrentIndex(j);
				}	
			}

		}else
		{
			widget->addWidget(child_widget);
		}
	}
	else if (strcmp(father->getName(),"ScrollArea")==0)
	{
		QScrollArea* widget = (QScrollArea*)father->getObject();
		widget->setWidget(child_widget);
	}
	////�����ڴ����Ծ���λ�ðڷſؼ�����Ҫ��geometry����,��Ҫ��װ������setGeometry�������ӿؼ��޷�ȷ��������
	QWidget* widget = (QWidget*)father->getObject();
	if (child->hasAttribute("geometry"))
	{
		child_widget->setParent(widget);
		std::vector<std::string> gv;
		std::string geometryStr = child->getAttribute("geometry");
		splitString(geometryStr,gv,",");
		if (gv.size()==4)
		{
			int x = STR_TO_INT(gv.at(0).c_str());
			int y = STR_TO_INT(gv.at(1).c_str());
			int w = STR_TO_INT(gv.at(2).c_str());
			int h = STR_TO_INT(gv.at(3).c_str());
			child_widget->setGeometry(x,y,w,h);
			child_widget->setFixedSize(w,h);
		}	
	}
}
//װ��Widget��Item
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndItem(ui_node* father,ui_node* child)
{
	if (strcmp(father->getName(),"Table")==0)
	{
		QTableWidget* widget =  (QTableWidget*)father->getObject();
		if (strcmp(child->getName(),"TableItem")==0&&child->hasAttribute("row")&&child->hasAttribute("col"))
		{
			QTableWidgetItem* item = (QTableWidgetItem*)child->getObject();
			int row = STR_TO_INT(child->getAttribute("row"));
			int col = STR_TO_INT(child->getAttribute("col"));
			widget->setItem(row,col,item);
		}

	}
	if (strcmp(child->getName(),"MenuSeparator")==0)
	{
		QWidget* widget = (QWidget*)father->getObject();
		QAction* action = (QAction*)child->getObject();
		action->setSeparator(true);
		widget->addAction(action);
	}
	if (strcmp(child->getName(),"Action")==0)
	{
		QWidget* widget = (QWidget*)father->getObject();
		QAction* action = (QAction*)child->getObject();
		action->setParent(widget);
		if (child->hasAttribute("text"))
		{
			action->setText(child->getAttribute("text"));
		}
		if (child->hasAttribute("icon"))
		{
			std::string url;
			getResImageUrl(url,child->getAttribute("icon"));
			QIcon* icon = new QIcon(url.c_str());
			action->setIcon(*icon);
		}
		if (child->hasAttribute("checkable"))
		{
			action->setCheckable(STR_TO_BOOL(child->getAttribute("checkable")));
		}
		if (child->hasAttribute("checked"))
		{
			action->setCheckable(true);
			action->setChecked(STR_TO_BOOL(child->getAttribute("checked")));
		}
		widget->addAction(action);
	}
}
//װ��Widget��Items
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndItems(ui_node* father,ui_node* child)
{
	if (strcmp(father->getName(),"Table")==0)
	{
		if (strcmp(child->getName(),"TableColumnItems")==0)
		{
			
			int col = STR_TO_INT(child->getAttribute("col"));
			int row = STR_TO_INT(child->getAttribute("row"));
			QTableWidget* table = (QTableWidget*)father->getObject();
			int width = 50;
			int height = 20;
			bool bH = false;
			if (child->hasAttribute("width"))
			{
				width = STR_TO_INT(child->getAttribute("width"));
				table->setColumnWidth(col,width);
			}
			if (child->hasAttribute("height"))
			{
				height = STR_TO_INT(child->getAttribute("height"));
				bH = true;
			}
			if (child->hasAttribute("resizeMode"))
			{
				table->horizontalHeader()->setSectionResizeMode(col,qt_standard::getHeaderResizeMode(child->getAttribute("resizeMode")));
				table->horizontalHeader()->resizeSection(col,width);
			}
			for (int i=0;i<child->getChildNum();i++)
			{
				if (bH)
				{
					table->setRowHeight(STR_TO_INT(child->getChild(i)->getAttribute("row")),
						height);
				}
				assembleNodes(father,child->getChild(i));
			}
		}
		if (strcmp(child->getName(),"TableRowItems")==0)
		{
			int col = STR_TO_INT(child->getAttribute("col"));
			int row = STR_TO_INT(child->getAttribute("row"));
			QTableWidget* table = (QTableWidget*)father->getObject();
			int width = 50;
			int height = 20;
			bool bW = false;
			if (child->hasAttribute("width"))
			{
				width = STR_TO_INT(child->getAttribute("width"));
				bW = true;
			}
			if (child->hasAttribute("height"))
			{
				height = STR_TO_INT(child->getAttribute("height"));
				table->setRowHeight(row,height);
			}
			if (child->hasAttribute("resizeMode"))
			{
				table->horizontalHeader()->setSectionResizeMode(row,qt_standard::getHeaderResizeMode(child->getAttribute("resizeMode")));
				table->horizontalHeader()->resizeSection(row,height);
			}
			for (int i=0;i<child->getChildNum();i++)
			{
				if (bW)
				{
					table->setColumnWidth(STR_TO_INT(child->getChild(i)->getAttribute("col")),
						width);
				}
				assembleNodes(father,child->getChild(i));
			}
		}
	}
}
//װ��Container��Widget
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleContainerAndWidget(ui_node* father,ui_node* child)
{
	if (strcmp(father->getName(),"MutexButtonBox")==0)
	{
		if (strcmp(child->getName(),"Button")==0)
		{
			sl_MutexButtonBox* box = (sl_MutexButtonBox*)father->getObject();
			sl_Button* child_widget = (sl_Button*)child->getObject();
			box->addChildButton(child_widget);
			assembleNodes(father->getParent(),child);
		}
		
	}	
	else if(strcmp(father->getName(),"ButtonGroup")==0)
	{
		if (strcmp(child->getName(),"Button")==0||strcmp(child->getName(),"RadioButton")==0
			||strcmp(child->getName(),"CheckBox")==0||strcmp(child->getName(),"ToolButton")==0)
		{
			QAbstractButton* btn = (QAbstractButton*)child->getObject();
			QButtonGroup* btnGroup = (QButtonGroup*)father->getObject();
			btnGroup->addButton(btn);
			assembleNodes(father->getParent(),child);
		}
	}
	else if(strcmp(father->getName(),"ActionGroup")==0)
	{
		if (strcmp(child->getName(),"Action")==0)
		{
			QAction* action = (QAction*)child->getObject();
			QActionGroup* actionGroup = (QActionGroup*)father->getObject();
			actionGroup->addAction(action);
			assembleNodes(father->getParent(),child);
		}
	}
	else if(strcmp(father->getName(),"VectorContainer")==0)
	{
		sl_VectorContainer* container = (sl_VectorContainer*)father->getObject();
		container->addChild(child->getObject());
		assembleNodes(father->getParent(),child);
	}
	else if(strcmp(father->getName(),"MapContainer")==0)
	{
		sl_MapContainer* container = (sl_MapContainer*)father->getObject();
		if (child->hasAttribute("key"))
		{
			container->addChild(STR_TO_INT(child->getAttribute("key")),child->getObject());
		}
		assembleNodes(father->getParent(),child);
	}
}

//���ڵ��е�����������ø�QObject�����ڴ��ݸ�����ִ����
//��ui_node�ڵ��object����
//������object object����ָ��, node �ڵ�ָ��
//����ֵ���Ƿ�����ɹ�
bool qt_ui_assembler::bindObjectWithNode(void* object,ui_node* node) 
{
	if (node->getType()==ui_node::WIDGET||node->getType()==ui_node::LAYOUT)
	{
		if (getUINodeFromObject(object))
		{
			return true;
		}
		QObject* qobject = (QObject*)object;
		QVariant variant;
		variant.setValue(node);
		qobject->setProperty("ui_node",variant);
		return true;
	}
	else if (node->getType()==ui_node::ITEM)
	{
		if (strcmp(node->getName(),"TreeWidgetItem")==0)
		{
			QTreeWidgetItem* item = (QTreeWidgetItem*)object;
			QVariant variant;
			variant.setValue(node);
			item->setData(0,Qt::UserRole,variant);	
			return true;
		}
		else
		{
			QObject* qobject = (QObject*)object;
			QVariant variant;
			variant.setValue(node);
			qobject->setProperty("ui_node",variant);
			return true;
		}
	}
	else
	{
		return false;
	}
}
//IDע��
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::registerID(ui_node* node)
{
	if (node->hasAttribute("id"))
	{
		std::string id = node->getAttribute("id");
		if (_IDMap.count(id.c_str()))
		{
			//�ظ�����ID	
		}
		else
		{
			_IDMap[id] = node->getObject();
			//����ȫ�ֵ�UINodeMap
			R::Instance()->addObjectGlobalMap(id.c_str(),node->getObject());
		}
	}
}
//��ö���ָ��
//������id ����id
//����ֵ������ָ��
void* qt_ui_assembler::getObjectByID(const char* id)
{
	IDObjectMapType::iterator it = _IDMap.find(id);
	if (it != _IDMap.end())
	{
		return it->second;
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: The object whose ID is %s does not exist!\n",id);
		printf(szMsg);
		return NULL;
	}
}
//����ÿ���ڵ��ʵ��
//������node �ڵ�ָ��
//����ֵ����
bool qt_ui_assembler::createUI(ui_node* node)
{
	if (node->getObject())
	{
		return true;
	}
	if (strcmp(node->getName(),"Button")==0)
	{
		node->setType(ui_node::WIDGET);
		//QPushButton* button = new QPushButton;
		sl_Button* button = new sl_Button;
		
		if (node->hasAttribute("needToConfirm"))
		{
			button->setNeedToConfirm(STR_TO_BOOL(node->getAttribute("needToConfirm")));
		}
		if (node->hasAttribute("available"))
		{
			button->setAvailable(STR_TO_BOOL(node->getAttribute("available")));
		}
		
		if (node->hasAttribute("flat"))
		{
			button->setFlat(STR_TO_BOOL(node->getAttribute("flat")));
		}
		node->setObject(button);
		if (bindObjectWithNode(button,node)) 
		{
			QObject::connect(button,SIGNAL(clicked()),_event_handler,SLOT(handle()));
		//	button->installEventFilter(_event_handler);
		}
	}
	else if (strcmp(node->getName(),"VLayout")==0)
	{
		node->setType(ui_node::LAYOUT);
		QVBoxLayout* vLayout = new QVBoxLayout;
		node->setObject(vLayout);
	}
	else if (strcmp(node->getName(),"HLayout")==0)
	{
		node->setType(ui_node::LAYOUT);
		QHBoxLayout* hLayout = new QHBoxLayout;
		node->setObject(hLayout);
	}
	else if (strcmp(node->getName(),"GridLayout")==0)
	{
		node->setType(ui_node::LAYOUT);
		QGridLayout* gridLayout = new QGridLayout;
		node->setObject(gridLayout);
	}
	else if (strcmp(node->getName(),"Label")==0)
	{
		node->setType(ui_node::WIDGET);
		QLabel* label = new QLabel;
		if (node->hasAttribute("text"))
		{
			std::string text=node->getAttribute("text"); 
			label->setText(STR_TO_RES_TEXT(str_replace_all(text,"\\n","\n").c_str()));
		}
		if (node->hasAttribute("align"))
		{
			label->setAlignment(qt_standard::getAlignment(node->getAttribute("align")));
		}
		node->setObject(label);
	}
	else if (strcmp(node->getName(),"LineEdit")==0)
	{
		node->setType(ui_node::WIDGET);
		QLineEdit* lineEdit = new QLineEdit;
		if (node->hasAttribute("text"))
		{
			lineEdit->setText(STR_TO_RES_TEXT(node->getAttribute("text")));
		}
		if (node->hasAttribute("readOnly"))
		{
			lineEdit->setReadOnly(STR_TO_BOOL(node->getAttribute("readOnly")));
		}
		if (node->hasAttribute("maxLength"))
		{
			lineEdit->setMaxLength(STR_TO_INT(node->getAttribute("maxLength")));
		}
		if (node->hasAttribute("inputMask"))
		{
			lineEdit->setInputMask(node->getAttribute("inputMask"));
		}
		if (node->hasAttribute("align"))
		{
			lineEdit->setAlignment(qt_standard::getAlignment(node->getAttribute("align")));
		}
		if (node->hasAttribute("echoMode"))
		{
			lineEdit->setEchoMode(qt_standard::getEchoMode(node->getAttribute("echoMode")));
		}
		//����������ʽ
		if (node->hasAttribute("validator"))
		{
			QValidator *validator = NULL;
			std::string str = node->getAttribute("validator");
			if (str.find(":")!=std::string::npos)
			{
				int i = str.find_first_of(":");
				std::string val = str.substr(i+1,str.length());
				std::string type = str.substr(0,i);
				if (strcmp(type.c_str(),"int")==0)
				{
					if (val.find(",")!=std::string::npos)
					{
						int j = val.find_first_of(",");
						int minInt = STR_TO_INT(val.substr(0,j).c_str());
						int maxInt = STR_TO_INT(val.substr(j+1,val.length()).c_str());
						validator = new QIntValidator(minInt,maxInt,NULL);
					}
				}
				else if (strcmp(type.c_str(),"double")==0)
				{
					if (val.find(",")!=std::string::npos)
					{
						int j = val.find_first_of(",");
						double minDouble = STR_TO_DOUBLE(val.substr(0,j).c_str());
						double maxDouble = STR_TO_DOUBLE(val.substr(j+1,val.length()).c_str());
						validator = new QDoubleValidator(minDouble,maxDouble,4,NULL);
					}
				}
				else if (strcmp(type.c_str(),"regExp")==0)
				{
					QRegExp rx(val.c_str());
					validator = new QRegExpValidator(rx,NULL);
				}
			}
			if (validator)
			{
				lineEdit->setValidator(validator);
			}	
		}
		node->setObject(lineEdit);
		if (bindObjectWithNode(lineEdit,node))
		{
			QObject::connect(lineEdit,SIGNAL(editingFinished()),_event_handler,SLOT(handle()));
			//widget->installEventFilter(_event_handler);
		}
	}
	else if (strcmp(node->getName(),"Spacing")==0)
	{
		QObject* object = new QObject;
		node->setType(ui_node::ITEM);
		node->setObject(object);
	}
	else if (strcmp(node->getName(),"Stretch")==0)
	{
		QObject* object = new QObject;
		node->setType(ui_node::ITEM);
		node->setObject(object);
	}
	else if (strcmp(node->getName(),"MutexButtonBox")==0)
	{
		node->setType(ui_node::CONTAINER);
		sl_MutexButtonBox* mutexBtnBox = new sl_MutexButtonBox;
		if (node->hasAttribute("buttonSelectedStyle"))
		{
			mutexBtnBox->setButtonSelectedStyle(node->getAttribute("buttonSelectedStyle"));
		}
		if (node->hasAttribute("buttonActivatedStyle"))
		{
			mutexBtnBox->setButtonActivatedStyle(node->getAttribute("buttonActivatedStyle"));
		}
		if (node->hasAttribute("buttonNormalStyle"))
		{
			mutexBtnBox->setButtonNormalStyle(node->getAttribute("buttonNormalStyle"));
		}
		mutexBtnBox->init();
		node->setObject(mutexBtnBox);
	}
	else if (strcmp(node->getName(),"Tabs")==0)
	{
		node->setType(ui_node::WIDGET);
		QTabWidget* tabs = new QTabWidget;
		if (node->hasAttribute("tabPosition"))
		{
			tabs->setTabPosition(qt_standard::getTabPosition(node->getAttribute("tabPosition")));
		}
		if (node->hasAttribute("movable"))
		{
			tabs->setMovable(STR_TO_BOOL(node->getAttribute("movable")));
		}
		if (node->hasAttribute("closable"))
		{
			tabs->setTabsClosable(STR_TO_BOOL(node->getAttribute("closable")));
		}
		node->setObject(tabs);
	}
	else if (strcmp(node->getName(),"Tab")==0)
	{
		node->setType(ui_node::WIDGET);
		QWidget* tab = new QWidget;
		node->setObject(tab);
	}
	else if (strcmp(node->getName(),"Spinner")==0)
	{
		node->setType(ui_node::WIDGET);
		if (node->hasAttribute("valueType")&&strcmp(node->getAttribute("valueType"),"double")==0)
		{
			QDoubleSpinBox* doubleSpinner = new QDoubleSpinBox;
			if (node->hasAttribute("rangeMax")&&node->hasAttribute("rangeMin"))
			{
				doubleSpinner->setRange(STR_TO_DOUBLE(node->getAttribute("rangeMin")),
					STR_TO_DOUBLE(node->getAttribute("rangeMax")));
			}
			if (node->hasAttribute("range"))
			{
				std::vector<std::string> rangeVec;
				std::string rangeStr = node->getAttribute("range");
				splitString(rangeStr,rangeVec,",");
				if (rangeVec.size()==2)
				{
					doubleSpinner->setRange(STR_TO_DOUBLE(rangeVec.at(0).c_str()),STR_TO_DOUBLE(rangeVec.at(1).c_str()));
				}
			}
			if (node->hasAttribute("singleStep"))
			{
				doubleSpinner->setSingleStep(STR_TO_DOUBLE(node->getAttribute("singleStep")));
			}
			if (node->hasAttribute("value"))
			{
				doubleSpinner->setValue(STR_TO_DOUBLE(node->getAttribute("value")));
			}
			node->setObject(doubleSpinner);
		}
		else
		{
			QSpinBox* spinner = new QSpinBox;
			if (node->hasAttribute("rangeMax")&&node->hasAttribute("rangeMin"))
			{
				spinner->setRange(STR_TO_INT(node->getAttribute("rangeMin")),
					STR_TO_INT(node->getAttribute("rangeMax")));
			}
			if (node->hasAttribute("range"))
			{
				std::vector<std::string> rangeVec;
				std::string rangeStr = node->getAttribute("range");
				splitString(rangeStr,rangeVec,",");
				if (rangeVec.size()==2)
				{
					spinner->setRange(STR_TO_INT(rangeVec.at(0).c_str()),STR_TO_INT(rangeVec.at(1).c_str()));
				}
			}
			if (node->hasAttribute("singleStep"))
			{
				spinner->setSingleStep(STR_TO_INT(node->getAttribute("singleStep")));
			}
			if (node->hasAttribute("value"))
			{
				spinner->setValue(STR_TO_INT(node->getAttribute("value")));
			}
			node->setObject(spinner);
		}
	}
	else if (strcmp(node->getName(),"VSplitter")==0)
	{
		node->setType(ui_node::WIDGET);
		QSplitter* vSplitter = new QSplitter(Qt::Vertical);
		node->setObject(vSplitter);
	}
	else if (strcmp(node->getName(),"HSplitter")==0)
	{
		node->setType(ui_node::WIDGET);
		QSplitter* hSplitter = new QSplitter(Qt::Horizontal);
		node->setObject(hSplitter);
	}
	else if (strcmp(node->getName(),"GroupBox")==0)
	{
		node->setType(ui_node::WIDGET);
		QGroupBox* groupBox = new QGroupBox;
		groupBox->setStyleSheet("QGroupBox{border-width:1px; border-style:solid; border-color:gray margin-top:1px} QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;padding:0 1px}");
		if (node->hasAttribute("text"))
		{
			groupBox->setTitle(STR_TO_RES_TEXT(node->getAttribute("text")));
		}
		//�Ƿ񻭱߿�
		if (node->hasAttribute("flat"))
		{
			groupBox->setFlat(STR_TO_BOOL(node->getAttribute("flat")));
		}
		if (node->hasAttribute("checkable"))
		{
			groupBox->setCheckable(STR_TO_BOOL(node->getAttribute("checkable")));
			if (node->hasAttribute("checked"))
			{
				groupBox->setChecked(STR_TO_BOOL(node->getAttribute("checked")));
			}else
			{
				groupBox->setChecked(true);
			}
		}
		node->setObject(groupBox);
		if (bindObjectWithNode(groupBox,node)) 
		{
			QObject::connect(groupBox,SIGNAL(clicked()),_event_handler,SLOT(handle()));
			//widget->installEventFilter(_event_handler);
		}

	}
	else if (strcmp(node->getName(),"ComboBox")==0)
	{
		node->setType(ui_node::WIDGET);
		QComboBox* comboBox = new QComboBox;
		for (int i=0;i<node->getChildNum();i++)
		{
			ui_node* childNode = node->getChild(i);
			if (strcmp(childNode->getName(),"ComboBoxItem")==0)
			{
				createUI(childNode);
				if (childNode->getObject()&&childNode->hasAttribute("text"))
				{
					comboBox->addItem(STR_TO_RES_TEXT(childNode->getAttribute("text")));
				}
			}
		}
		if (node->hasAttribute("initIndex"))
		{
			comboBox->setCurrentIndex(STR_TO_INT(node->getAttribute("initIndex")));
		}
		node->setObject(comboBox);
		if (bindObjectWithNode(comboBox,node))
		{
			QObject::connect(comboBox,SIGNAL(currentIndexChanged(int)),_event_handler,SLOT(handle(int)));
		}
	}
	else if (strcmp(node->getName(),"ComboBoxItem")==0)
	{
		node->setType(ui_node::ITEM);
		QObject* object = new QObject;
		node->setObject(object);
		bindObjectWithNode(object,node);
	}
	else if (strcmp(node->getName(),"Widget")==0)
	{
		node->setType(ui_node::WIDGET);
		QWidget* widget = new QWidget;
		node->setObject(widget);

	}
	else if (strcmp(node->getName(),"TextEdit")==0)
	{
		node->setType(ui_node::WIDGET);
		QTextEdit* textEdit = new QTextEdit;
		if (node->hasAttribute("lineWrap"))
		{
			int w = STR_TO_INT(node->getAttribute("lineWrap"));
			textEdit->setLineWrapMode(QTextEdit::FixedPixelWidth);
			textEdit->setLineWrapColumnOrWidth(w);
			textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		}
		if (node->hasAttribute("text"))
		{
			std::string text=node->getAttribute("text"); 
			textEdit->setText(STR_TO_RES_TEXT(str_replace_all(text,"\\n","\n").c_str()));
		}
		if (node->hasAttribute("readOnly"))
		{
			textEdit->setReadOnly(STR_TO_BOOL(node->getAttribute("readOnly")));
		}
		node->setObject(textEdit);
	}

	else if (strcmp(node->getName(),"Table")==0)
	{
		node->setType(ui_node::WIDGET);
		QTableWidget* table = new QTableWidget(1,1);
		if (node->hasAttribute("col"))
		{
			table->setColumnCount(STR_TO_INT(node->getAttribute("col")));
		}
		if (node->hasAttribute("row"))
		{
			table->setRowCount(STR_TO_INT(node->getAttribute("row")));
		}
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);  //���Ĭ�ϲ��ɱ༭
		if (node->hasAttribute("editable"))
		{
			if (STR_TO_BOOL(node->getAttribute("editable")))
			{
				table->setEditTriggers(QAbstractItemView::DoubleClicked);
			}
		}
		if (node->hasAttribute("vHeaderVisible"))
		{
			table->verticalHeader()->setVisible(STR_TO_BOOL(node->getAttribute("vHeaderVisible")));
		}
		if (node->hasAttribute("hHeaderVisible"))
		{
			table->horizontalHeader()->setVisible(STR_TO_BOOL(node->getAttribute("hHeaderVisible")));
		}
		if (node->hasAttribute("hHeaderLabels"))
		{
			table->setHorizontalHeaderLabels(STR_TO_STR_VECTOR(node->getAttribute("hHeaderLabels")));
		}
		if (node->hasAttribute("vHeaderLabels"))
		{
			table->setVerticalHeaderLabels(STR_TO_STR_VECTOR(node->getAttribute("vHeaderLabels")));
		}

		//table->resizeColumnsToContents();  //ʹ����п���������Ӧ 20151103
		//table->resizeRowsToContents(); //ʹ����п���������Ӧ
		table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  //ʹ����п������ݴ�С��Ӧ
		table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		table->horizontalHeader()->setSectionsMovable(true);  //ʹ��ͷ������ק�ı��С
		table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
		table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
		table->verticalHeader()->setSectionsMovable(true);
		
		
		if (node->hasAttribute("vHeaderResizeMode"))
		{
			table->verticalHeader()->setSectionResizeMode(qt_standard::getHeaderResizeMode(node->getAttribute("vHeaderResizeMode")));
		}
		if (node->hasAttribute("hHeaderResizeMode"))
		{
			table->horizontalHeader()->setSectionResizeMode(qt_standard::getHeaderResizeMode(node->getAttribute("hHeaderResizeMode")));
		}		

        if (node->hasAttribute("hMinimumSectionSize"))
        {
            table->horizontalHeader()->setMinimumSectionSize(STR_TO_INT(node->getAttribute("hMinimumSectionSize"))); //���ñ�ͷ��С�ߴ�
        }
        else
        {
            table->horizontalHeader()->setMinimumSectionSize(60);
        }
        if (node->hasAttribute("vMinimumSectionSize"))
        {
            table->verticalHeader()->setMinimumSectionSize(STR_TO_INT(node->getAttribute("vMinimumSectionSize")));
        }
        else
        {
            table->verticalHeader()->setMinimumSectionSize(20);
        }
        //ssx���ô�ֱ��ͷ��С���40
        if (node->hasAttribute("vMinimumHeadeSize"))
        {
           table->verticalHeader()->setMinimumWidth(STR_TO_INT(node->getAttribute("vMinimumHeadeSize")));
        }
        else
        {
            table->verticalHeader()->setMinimumWidth(40);
        }
		node->setObject(table);
		if (bindObjectWithNode(table,node))
		{
			QObject::connect(table,SIGNAL(cellDoubleClicked(int,int)),_event_handler,SLOT(handle(int,int)));
			//QObject::connect(table,SIGNAL(cellClicked(int,int)),_event_handler,SLOT(handle(int,int)));
		}
	}
	else if (strcmp(node->getName(),"TableItem")==0)
	{
		node->setType(ui_node::ITEM);
		QTableWidgetItem* tableItem = new QTableWidgetItem;
		if (node->hasAttribute("text"))
		{
			string text=node->getAttribute("text"); 
			tableItem->setText(STR_TO_RES_TEXT(str_replace_all(text,"\\n","\n").c_str()));
		}
		if (node->hasAttribute("background-color"))
		{
			tableItem->setBackgroundColor(getResText(node->getAttribute("background-color")));
		}
		//����Ĭ�Ͼ���
		tableItem->setTextAlignment(Qt::AlignCenter);
		if (node->hasAttribute("text-align"))
		{
			tableItem->setTextAlignment(qt_standard::getAlignment(node->getAttribute("text-align")));
		}
		node->setObject(tableItem);
	}
	else if (strcmp(node->getName(),"TableColumnItems")==0)
	{
		node->setType(ui_node::ITEMS);
		QObject* object = new QObject;
		if (node->hasAttribute("col")&&node->hasAttribute("size"))
		{
			int size = STR_TO_INT(node->getAttribute("size"));
			int row = 0;
			bool bHasText =  false;
			bool bHasBackgroundColor = false;
			bool bHasTexts = false;
			string text="";
			string backgroundColor="";
			string textAlign = "center";
			std::vector<std::string> stringList;
			if (node->hasAttribute("row"))
			{
				row = STR_TO_INT(node->getAttribute("row"));
			}
			if (node->hasAttribute("text"))
			{
				text=node->getAttribute("text"); 
				bHasText = true;
			}
			if (node->hasAttribute("texts"))
			{
				string texts = node->getAttribute("texts");
				splitString(texts,stringList,";;");
				bHasTexts = true;
			}
			if (node->hasAttribute("background-color"))
			{
				backgroundColor = getResText(node->getAttribute("background-color"));
				bHasBackgroundColor = true;
			}
			if (node->hasAttribute("text-align"))
			{
				textAlign = node->getAttribute("text-align");
			}

			for (int i=0;i<size;i++)
			{
				ui_node* child_node = new ui_node;
				child_node->setName("TableItem");
				child_node->addAttribute("col",node->getAttribute("col"));
				char rowStr[50];
				sprintf(rowStr,"%d",row);
				child_node->addAttribute("row",rowStr);
				if (bHasText)
				{
					child_node->addAttribute("text",text.c_str());
				}
				if (bHasBackgroundColor)
				{
					child_node->addAttribute("background-color",backgroundColor.c_str());
				}
				if (bHasTexts)
				{
					if (i<stringList.size())
					{
						child_node->addAttribute("text",stringList.at(i).c_str());
					}	
				}
				child_node->addAttribute("text-align",textAlign.c_str());
				createUI(child_node);
				node->addChild(child_node);
				row++;
			}	
		}
		node->setObject(object);

	}
	else if (strcmp(node->getName(),"TableRowItems")==0)
	{
		node->setType(ui_node::ITEMS);
		QObject* object = new QObject;
		if (node->hasAttribute("row")&&node->hasAttribute("size"))
		{
			int size = STR_TO_INT(node->getAttribute("size"));
			int col=0;
			bool bHasText =  false;
			bool bHasBackgroundColor = false;
			bool bHasTexts = false;
			string text="";
			string backgroundColor="";
			string textAlign = "center";
			std::vector<std::string> stringList;
			if (node->hasAttribute("col"))
			{
				col = STR_TO_INT(node->getAttribute("col"));
			}
			if (node->hasAttribute("text"))
			{
				text=node->getAttribute("text"); 
				bHasText = true;
			}
			if (node->hasAttribute("background-color"))
			{
				backgroundColor = getResText(node->getAttribute("background-color"));
				bHasBackgroundColor = true;
			}
			if (node->hasAttribute("texts"))
			{
				string texts = node->getAttribute("texts");
				splitString(texts,stringList,";;");
				bHasTexts = true;
			}
			if (node->hasAttribute("text-align"))
			{
				textAlign = node->getAttribute("text-align");
			}
			for (int i=0;i<size;i++)
			{
				ui_node* child_node = new ui_node;
				child_node->setName("TableItem");
				child_node->addAttribute("row",node->getAttribute("row"));
				char colStr[50];
				sprintf(colStr,"%d",col);
				child_node->addAttribute("col",colStr);
				if (bHasText)
				{
					child_node->addAttribute("text",text.c_str());
				}
				if (bHasBackgroundColor)
				{
					child_node->addAttribute("background-color",backgroundColor.c_str());
				}
				if (bHasTexts)
				{
					if (i<stringList.size())
					{
						child_node->addAttribute("text",stringList.at(i).c_str());
					}	
				}
				child_node->addAttribute("text-align",textAlign.c_str());
				createUI(child_node);
				node->addChild(child_node);
				col++;
			}	
		}
		node->setObject(object);
	}
	else if (strcmp(node->getName(),"Slider")==0)
	{
		node->setType(ui_node::WIDGET);
		QSlider* slider = new QSlider;
		node->setObject(slider);
	}
	else if (strcmp(node->getName(),"VSlider")==0)
	{
		node->setType(ui_node::WIDGET);
		QSlider* vSlider = new QSlider(Qt::Vertical);
		node->setObject(vSlider);
	}
	else if (strcmp(node->getName(),"HSlider")==0)
	{
		node->setType(ui_node::WIDGET);
		QSlider* hSlider = new QSlider(Qt::Horizontal);
		node->setObject(hSlider);
		//shisx 
        if (bindObjectWithNode(hSlider,node))
        {
            QObject::connect(hSlider,SIGNAL(valueChanged(int)),_event_handler,SLOT(handle(int)));
        }
	}
	else if (strcmp(node->getName(),"VScrollBar")==0)
	{
		node->setType(ui_node::WIDGET);
		QScrollBar* vScrollBar = new QScrollBar(Qt::Vertical);
		node->setObject(vScrollBar);
	}
	else if (strcmp(node->getName(),"HScrollBar")==0)
	{
		node->setType(ui_node::WIDGET);
		QScrollBar* hScrollBar = new QScrollBar(Qt::Horizontal);
		node->setObject(hScrollBar);
	} 
	else if (strcmp(node->getName(),"Dial")==0)
	{
		node->setType(ui_node::WIDGET);
		QDial* dial = new QDial;
		node->setObject(dial);
	}
	else if (strcmp(node->getName(),"RadioButton")==0)
	{
		node->setType(ui_node::WIDGET);
		QRadioButton* radioBtn = new QRadioButton;
		node->setObject(radioBtn);
		if (bindObjectWithNode(radioBtn,node)) 
		{
			QObject::connect(radioBtn,SIGNAL(clicked()),_event_handler,SLOT(handle()));
		}
	}
	else if (strcmp(node->getName(),"ToolButton")==0)
	{
		node->setType(ui_node::WIDGET);
		QToolButton* toolBtn = new QToolButton;
		node->setObject(toolBtn);
		if (bindObjectWithNode(toolBtn,node)) 
		{
			QObject::connect(toolBtn,SIGNAL(clicked()),_event_handler,SLOT(handle()));
		}
	}
	else if (strcmp(node->getName(),"CheckBox")==0)
	{
		node->setType(ui_node::WIDGET);
		QCheckBox* checkBox = new QCheckBox;
		if (node->hasAttribute("checkState"))
		{
			checkBox->setCheckState(qt_standard::getCheckState(node->getAttribute("checkState")));
		}
		node->setObject(checkBox);
		if (bindObjectWithNode(checkBox,node))
		{
			QObject::connect(checkBox,SIGNAL(clicked()),_event_handler,SLOT(handle()));
		}
	}

	else if (strcmp(node->getName(),"Frame")==0)
	{
		node->setType(ui_node::WIDGET);
		QFrame* frame = new QFrame;
		if (node->hasAttribute("shape"))
		{
			frame->setFrameShape(qt_standard::getFrameShape(node->getAttribute("shape")));
		}
		if (node->hasAttribute("shadow"))
		{
			frame->setFrameShadow(qt_standard::getFrameShadow(node->getAttribute("shadow")));
		}
		if (node->hasAttribute("lineWidth"))
		{
			frame->setLineWidth(STR_TO_INT(node->getAttribute("lineWidth")));
		}
		node->setObject(frame);
	}
	else if (strcmp(node->getName(),"GLWidget")==0)
	{
		node->setType(ui_node::WIDGET);
		QGLWidget* glwidget = new QGLWidget;
		node->setObject(glwidget);
	}
	else if (strcmp(node->getName(),"ScrollArea")==0)
	{
		node->setType(ui_node::WIDGET);
		QScrollArea* scrollArea = new QScrollArea;
		node->setObject(scrollArea);
	}
	else if (strcmp(node->getName(),"DeclarativeView")==0)
	{
		node->setType(ui_node::WIDGET);
        QQuickView* declarativeView = new QQuickView;
		if (node->hasAttribute("source"))
		{
			std::string urlStr;
			getResQmlUrl(urlStr,node->getAttribute("source"));
			declarativeView->setSource(QUrl::fromLocalFile(urlStr.c_str()));
			
		}
		if (node->hasAttribute("resizeMode"))
		{
			if (strcmp(node->getAttribute("resizeMode"),"SizeViewToRootObject")==0)
			{
				declarativeView->setResizeMode(QQuickView::SizeViewToRootObject);
			}
			else if (strcmp(node->getAttribute("resizeMode"),"SizeRootObjectToView")==0)
			{
				declarativeView->setResizeMode(QQuickView::SizeRootObjectToView);
			}
		}

		if (node->hasAttribute("graphicSystem"))
		{
			//if (strcmp(node->getAttribute("graphicSystem"),"gl")==0)
			//{
			//	QGLFormat format = QGLFormat::defaultFormat();
			//	format.setSampleBuffers(false);
			//	format.setSwapInterval(1);
			//	QGLWidget* glWidget = new QGLWidget(/*format*/);
			//	glWidget->setAutoFillBackground(false);
			//	declarativeView->setRenderTarget(glWidget->grabFrameBuffer());
			//}		
		}

		node->setObject(declarativeView);
	}
	else if (strcmp(node->getName(),"TableLayout")==0)
	{
		node->setType(ui_node::LAYOUT);
		//QFormLayout* hlayout = new QFormLayout;
		QGridLayout* layout = new QGridLayout;
		node->setObject(layout);
	}
	else if (strcmp(node->getName(),"TableRow")==0)
	{
		node->setType(ui_node::ITEM);
		QObject* object = new QObject;
		node->setObject(object);
	}
#ifdef USE_QCUSTOM_PLOT   //����QCustomPlot����ʱ������
	else if (strcmp(node->getName(),"CustomPlot")==0)
	{
		node->setType(ui_node::WIDGET);
		QCustomPlot* plot = new QCustomPlot;

		if (node->hasAttribute("interactions"))
		{
			plot->setInteractions(qt_standard::getQCPInteractions(node->getAttribute("interactions")));
		}
		if (node->hasAttribute("interaction"))
		{
			plot->setInteraction(qt_standard::getQCPInteraction(node->getAttribute("interaction")));
		}
		if (node->hasAttribute("background-color"))
		{
			plot->setBackground(QColor(QString(getResText(node->getAttribute("background-color")))));
		}
		if (node->hasAttribute("legendVisible"))
		{
			plot->legend->setVisible(STR_TO_BOOL(node->getAttribute("legendVisible")));
		}
		for (int i=0;i<node->getChildNum();i++)
		{
			ui_node* childNode = node->getChild(i);
			QCPAxis* axis = NULL;
			//ȷ��Axis����һ��
			if (strcmp(childNode->getName(),"XAxis")==0||strcmp(childNode->getName(),"XLabel")==0)
			{
				axis = plot->xAxis;
			}
			else if (strcmp(childNode->getName(),"YAxis")==0||strcmp(childNode->getName(),"YLabel")==0)
			{
				axis = plot->yAxis;
			}
			else if (strcmp(childNode->getName(),"XAxis2")==0||strcmp(childNode->getName(),"XLabel2")==0)
			{
				axis = plot->xAxis2;
			}
			else if (strcmp(childNode->getName(),"YAxis2")==0||strcmp(childNode->getName(),"YLabel2")==0)
			{
				axis = plot->yAxis2;
			}
			else if (strcmp(childNode->getName(),"Title")==0)
			{
				if (childNode->hasAttribute("text"))
				{
					QCPPlotTitle* title = new QCPPlotTitle(plot, childNode->getAttribute("text"));
					plot->plotLayout()->insertRow(0);
					plot->plotLayout()->addElement(0, 0, title);
					if (childNode->hasAttribute("color"))
					{
						title->setTextColor(QColor(childNode->getAttribute("color")));
					}
					if (childNode->hasAttribute("font"))
					{
						title->setFont(qt_standard::getStandardFont(childNode->getAttribute("font")));
					}	
				}		
			}
			if (!axis)
			{
				continue;
			}
			axis->setVisible(true);//����������ɼ�

			//��������
			if (strcmp(childNode->getName(),"XAxis")==0||strcmp(childNode->getName(),"YAxis")==0
				||strcmp(childNode->getName(),"XAxis2")==0||strcmp(childNode->getName(),"YAxis2")==0)
			{
				if (childNode->hasAttribute("color"))
				{
					QPen pen;
					pen.setColor(QColor(childNode->getAttribute("color")));
					axis->setBasePen(pen);
					axis->setTickPen(pen);
					axis->setSubTickPen(pen);
				}
				if (childNode->hasAttribute("tickLabelColor"))
				{
					axis->setTickLabelColor(QColor(QString(childNode->getAttribute("tickLabelColor"))));
				}
				if (childNode->hasAttribute("font"))
				{
					axis->setTickLabelFont(qt_standard::getStandardFont(childNode->getAttribute("font")));
				}
				if (childNode->hasAttribute("min"))
				{
					axis->setRangeLower(STR_TO_DOUBLE(childNode->getAttribute("min")));
				}
				if (childNode->hasAttribute("max"))
				{
					axis->setRangeUpper(STR_TO_DOUBLE(childNode->getAttribute("max")));
				}
			}
			//����Label
			else if(strcmp(childNode->getName(),"XLabel")==0||strcmp(childNode->getName(),"YLabel")==0
				||strcmp(childNode->getName(),"XLabel2")==0||strcmp(childNode->getName(),"YLabel2")==0)
			{
				if (childNode->hasAttribute("color"))
				{
					axis->setLabelColor(QColor(QString(childNode->getAttribute("color"))));
				}
				if (childNode->hasAttribute("text"))
				{
					axis->setLabel(childNode->getAttribute("text"));
				}
				if (childNode->hasAttribute("font"))
				{
					axis->setLabelFont(qt_standard::getStandardFont(childNode->getAttribute("font")));
				}	
			}
		}
		node->setObject(plot);

	}
#endif
	else if (strcmp(node->getName(),"ProgressBar")==0)
	{
		node->setType(ui_node::WIDGET);
		QProgressBar* progressBar = new QProgressBar;
		if (node->hasAttribute("rangeMax"))
		{
			progressBar->setMaximum(STR_TO_INT(node->getAttribute("rangeMax")));
		}
		if (node->hasAttribute("rangeMin"))
		{
			progressBar->setMinimum(STR_TO_INT(node->getAttribute("rangeMin")));
		}
		if (node->hasAttribute("range"))
		{
			std::vector<std::string> rangeVec;
			std::string rangeStr = node->getAttribute("range");
			splitString(rangeStr,rangeVec,",");
			if (rangeVec.size()==2)
			{
				progressBar->setRange(STR_TO_INT(rangeVec.at(0).c_str()),STR_TO_INT(rangeVec.at(1).c_str()));
			}
		}
		if (node->hasAttribute("value"))
		{
			progressBar->setValue(STR_TO_INT(node->getAttribute("value")));
		}
		node->setObject(progressBar);
		if (bindObjectWithNode(progressBar,node))
		{
			QObject::connect(progressBar,SIGNAL(valueChanged(int)),_event_handler,SLOT(handle(int)));
		}
	}
	else if (strcmp(node->getName(),"StackedWidget")==0)
	{
		node->setType(ui_node::WIDGET);
		QStackedWidget* stackedWidget = new QStackedWidget;
		node->setObject(stackedWidget);
		if (bindObjectWithNode(stackedWidget,node)) 
		{
			//widget->installEventFilter(_event_handler);
		}
	}
	else if (strcmp(node->getName(),"StackedLayout")==0)
	{
		node->setType(ui_node::LAYOUT);
		QStackedLayout* stackedLayout = new QStackedLayout;
		node->setObject(stackedLayout);
		bindObjectWithNode(stackedLayout,node);
	}
	else if (strcmp(node->getName(),"TreeWidget")==0)
	{
		node->setType(ui_node::WIDGET);
		QTreeWidget* treeWidget = new QTreeWidget;
		if (node->hasAttribute("colCount"))
		{
			treeWidget->setColumnCount(STR_TO_INT(node->getAttribute("colCount")));
		}else
		{
			treeWidget->setColumnCount(1);
		}
		if (node->hasAttribute("text"))
		{
			treeWidget->setHeaderLabel(node->getAttribute("text"));
		}
		if (node->hasAttribute("headerLabels"))
		{
			treeWidget->setHeaderLabels(STR_TO_STR_VECTOR(node->getAttribute("headerLabels")));
		}
		//���TreeWidget�ĸ��ڵ�
		for (int i=0;i<node->getChildNum();i++)
		{
			ui_node* childNode = node->getChild(i);
			createTreeUI(childNode);
			if (childNode->getObject())
			{
				QTreeWidgetItem* item = (QTreeWidgetItem*)childNode->getObject();
				treeWidget->addTopLevelItem(item);
			}	
		}
		//Ĭ�������ӽڵ�ȫ��չ��
		treeWidget->expandAll();
		node->setObject(treeWidget);
		//���ѡ��仯����Ӧ
		if (bindObjectWithNode(treeWidget,node))
		{
			//QObject::connect(treeWidget,SIGNAL(itemSelectionChanged()),_event_handler,SLOT(handle()));
			//QObject::connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),_event_handler,SLOT(handle(QTreeWidgetItem*,int)));
			QObject::connect(treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),_event_handler,SLOT(handle(QTreeWidgetItem*,int)));
		}

	}
	else if (strcmp(node->getName(),"VToolBar")==0)
	{
		node->setType(ui_node::WIDGET);
		QToolBar* vToolBar = new QToolBar;
		vToolBar->setOrientation(Qt::Vertical);
		if (node->hasAttribute("toolButtonStyle"))
		{
			vToolBar->setToolButtonStyle(qt_standard::getToolButtonStyle(node->getAttribute("toolButtonStyle")));
		}else
		{
			vToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
		}
		node->setObject(vToolBar);
	}
	else if (strcmp(node->getName(),"HToolBar")==0)
	{
		node->setType(ui_node::WIDGET);
		QToolBar* hToolBar = new QToolBar;
		hToolBar->setOrientation(Qt::Horizontal);
		if (node->hasAttribute("toolButtonStyle"))
		{
			hToolBar->setToolButtonStyle(qt_standard::getToolButtonStyle(node->getAttribute("toolButtonStyle")));
		}else
		{
			hToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
		}
		node->setObject(hToolBar);
	}
	else if (strcmp(node->getName(),"Menu")==0)
	{
		node->setType(ui_node::WIDGET);
		QMenu* menu = new QMenu;
		node->setObject(menu);
	}
	else if (strcmp(node->getName(),"Action")==0)
	{
		node->setType(ui_node::ITEM);
		QAction* action = new QAction(NULL);
		node->setObject(action);
		//���action����Ӧ
		if (bindObjectWithNode(action,node))
		{
			QObject::connect(action,SIGNAL(triggered()),_event_handler,SLOT(handle()));
		}
	}
	else if (strcmp(node->getName(),"MenuSeparator")==0)
	{
		node->setType(ui_node::ITEM);
		//Separator��һ�������QAction
		QAction* actionMenu = new QAction(NULL);
		node->setObject(actionMenu);
	}
	//ButtonGroup������ʢ�Ű�ť�ģ���Ҫ��RadioButton�Ļ�����������
	else if (strcmp(node->getName(),"ButtonGroup")==0)
	{
		node->setType(ui_node::CONTAINER);
		QButtonGroup* btnGroup = new QButtonGroup();
		node->setObject(btnGroup);
	}
	//ActionGroup������ʢ��Action�ģ���Ҫ��Action�Ļ�����������
	else if (strcmp(node->getName(),"ActionGroup")==0)
	{
		node->setType(ui_node::CONTAINER);
		QActionGroup* actionGroup = new QActionGroup(NULL);
		node->setObject(actionGroup);
	}
	else if (strcmp(node->getName(),"ImageWidget")==0)
	{
		node->setType(ui_node::WIDGET);
		sl_ImageWidget* imageWidget = new sl_ImageWidget();
		if (node->hasAttribute("image"))
		{
			imageWidget->setImage(node->getAttribute("image"));
		}
		if (node->hasAttribute("width"))
		{
			imageWidget->setWidth(STR_TO_INT(node->getAttribute("width")));
		}
		if (node->hasAttribute("height"))
		{
			imageWidget->setHeight(STR_TO_INT(node->getAttribute("height")));
		}
		node->setObject(imageWidget);
	}
	else if (strcmp(node->getName(),"AnimationWidget")==0)
	{
		node->setType(ui_node::WIDGET);
		node->addAttribute("align","top"); //Ĭ���ö�
		sl_AnimationWidget* animationWidget = new sl_AnimationWidget;
		if (node->hasAttribute("width"))
		{
			animationWidget->setWidth(STR_TO_INT(node->getAttribute("width")));
		}
		if (node->hasAttribute("height"))
		{
			animationWidget->setHeight(STR_TO_INT(node->getAttribute("height")));
		}
		if (node->hasAttribute("image"))
		{
			animationWidget->setAnimation(node->getAttribute("image"));
		}
		node->setObject(animationWidget);
	}
	else if (strcmp(node->getName(),"FileSystemWidget")==0)
	{
		node->setType(ui_node::WIDGET);
		QFileSystemModel* model = new QFileSystemModel;
		model->setRootPath("");
		if (node->hasAttribute("rootPath"))
		{
			model->setRootPath(node->getAttribute("rootPath"));
		}
		QTreeView* tree = new QTreeView;
		tree->setModel(model);
		// Demonstrating look and feel features
		tree->setAnimated(false);
		tree->setIndentation(20);
		tree->setSortingEnabled(true);
		tree->setWindowTitle(QObject::tr("Dir View"));
		node->setObject(tree);
	}
	else if (strcmp(node->getName(),"DateTimeEdit")==0)
	{
		node->setType(ui_node::WIDGET);
		QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());
		node->setObject(dateEdit);
	}
	else if (strcmp(node->getName(),"TitleBar")==0)
	{
		node->setType(ui_node::CUSTOMER);
		node->addAttribute("align","top"); //Ĭ���ö�
		TitleBar* widget = new TitleBar;
		
		node->setObject(widget);
	}
	else if (strcmp(node->getName(),"VectorContainer")==0)
	{
		node->setType(ui_node::CONTAINER);
		sl_VectorContainer* container = new sl_VectorContainer;
		node->setObject(container);
	}
	else if (strcmp(node->getName(),"MapContainer")==0)
	{
		node->setType(ui_node::CONTAINER);
		sl_MapContainer* container = new sl_MapContainer;
		node->setObject(container);
	}
	else
	{
		/*************���ж��Ƿ����û��Զ���Widget*******************///20150925
		if (R::getCustomWidget(node->getName())) //����ֻ����Widget��Ŀؼ�
		{
			node->setType(ui_node::WIDGET);
			node->setObject(R::getCustomWidget(node->getName()));
		}
		else
		{
			if (!node->getObject())
			{
				if (strcmp("Holder",node->getName())==0)
				{
					if (node->hasAttribute("id"))
					{
						char szMsg[1024];
						sprintf(szMsg, "QtFrameWork ERROR: The Holder node whose id is \"%s\" is not bounded! Please check weather its id exists in ui resource! \n",node->getAttribute("id"));
						printf(szMsg);
					}
					else
					{
						char szMsg[1024];
						sprintf(szMsg, "QtFrameWork ERROR: Create UI %s failed! Holder node should be bounded to the ui resource!\n",node->getName());
						printf(szMsg);
					}
					return false;
				}
				if (node->hasAttribute("id"))
				{
					char szMsg[1024];
					sprintf(szMsg, "QtFrameWork ERROR: Create UI %s whose id is \"%s\" failed!! Please check if the name of the node is correct!\n",node->getName(),node->getAttribute("id"));
					printf(szMsg);
				}
				else
				{
					char szMsg[1024];
					sprintf(szMsg, "QtFrameWork ERROR: Create UI %s failed!! Please check if the name of the node is correct!\n",node->getName());
					printf(szMsg);
				}
				return false;
			}
		}
	}
	//*************Widgetͨ����������**********************//
	if(node->getType()==ui_node::WIDGET)
	{
		ParseWidgetCommonAttribute(node);
	}
	//*************Layoutͨ����������**********************//
	if (node->getType()==ui_node::LAYOUT)
	{
		ParseLayoutCommonAttribute(node);
	}
	//*************���ñ�����Ԫ�����е�����**********************//
	ParseObjectProperty(node);
	 //����ID�Ŀؼ�����map
	registerID(node);
	
	return true;
}
//����Widget���ͽڵ�Ĺ�������
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::ParseWidgetCommonAttribute(ui_node* node)
{
	QWidget* widget = (QWidget*)node->getObject();
	//��Widget�����¼�������,��ʱ������������¼��������˵���
	if (node->hasAttribute("menu"))
	{
		//����Widget��node
		if (bindObjectWithNode(widget,node))
		{
			widget->installEventFilter(_event_handler);
			string menuID = node->getAttribute("menu");
			string str="@menu/";
			if (menuID.find(str)!=std::string::npos)
			{
				menuID = menuID.substr(menuID.find_first_of(str)+6);
				ui_node* menuRootNode = R::Instance()->getMenuResource(menuID.c_str());
				if (menuRootNode)
				{
					//ʵ������װ��˵�
					parseUITree(menuRootNode);
				}	
			}
		}
	}

	if (node->hasAttribute("toolpanel"))
	{
		//����Widget��node
		if (bindObjectWithNode(widget,node))
		{
			//widget->installEventFilter(_event_handler);
			string toolpanelID = node->getAttribute("toolpanel");
			string str="@toolpanel/";
			if (toolpanelID.find(str)!=std::string::npos)
			{
				toolpanelID = toolpanelID.substr(toolpanelID.find_first_of(str)+11);
				ui_node* panelRootNode = R::Instance()->getToolpanelResource(toolpanelID.c_str());
				if (panelRootNode)
				{
					//ʵ������װ��˵�
					sl_ToolPanel* panel = new sl_ToolPanel(panelRootNode);
					panel->setParent(widget);
				}	
			}
		}
	}

	//�ؼ�����С�ߴ�
	const variant* variantWMW = R::Instance()->getConfigResource("WidgetMinimumWidth");
	if (variantWMW)
	{
		int w = R::Instance()->getConfigResource("WidgetMinimumWidth")->value<int>();
		widget->setMinimumWidth(variantWMW->value<int>()); 
	}
	const variant* variantWMH = R::Instance()->getConfigResource("WidgetMinimumHeight");
	if (variantWMH)
	{
		widget->setMinimumHeight(variantWMH->value<int>()); 
	}
	//����ָ���ؼ���С�ߴ�
	if (node->hasAttribute("minWidth"))
	{
		widget->setMinimumWidth(STR_TO_INT(node->getAttribute("minWidth")));
	}
	if (node->hasAttribute("minHeight"))
	{
		widget->setMinimumHeight(STR_TO_INT(node->getAttribute("minHeight")));
	}
	//���ÿؼ��Ƿ����
	if (node->hasAttribute("disabled"))
	{
		widget->setDisabled(STR_TO_BOOL(node->getAttribute("disabled")));
	}
	//���ÿؼ��Ƿ�ɼ�
	if (node->hasAttribute("visible"))
	{
		widget->setVisible(STR_TO_BOOL(node->getAttribute("visible")));
	}
	//���ÿؼ��ĳ�ʼ��С
	if (node->hasAttribute("width"))
	{
		widget->setFixedWidth(STR_TO_INT(node->getAttribute("width")));
	}
	if (node->hasAttribute("height"))
	{
		widget->setFixedHeight(STR_TO_INT(node->getAttribute("height")));
	}
	if (node->hasAttribute("size"))
	{
		std::vector<std::string> sizeStrVec;
		std::string sizeStr = node->getAttribute("size");
		splitString(sizeStr,sizeStrVec,",");
		if (sizeStrVec.size()==2)
		{
			int w = STR_TO_INT(sizeStrVec.at(0).c_str());
			int h = STR_TO_INT(sizeStrVec.at(1).c_str());
			widget->setFixedSize(w,h);
		}
	}
	if (node->hasAttribute("minSize"))
	{
		std::vector<std::string> sizeStrVec;
		std::string sizeStr = node->getAttribute("minSize");
		splitString(sizeStr,sizeStrVec,",");
		if (sizeStrVec.size()==2)
		{
			int w = STR_TO_INT(sizeStrVec.at(0).c_str());
			int h = STR_TO_INT(sizeStrVec.at(1).c_str());
			widget->setMinimumSize(w,h);
		}
	}
	//����Widget�����ڲ��ؼ�����ʽ
	if (node->hasAttribute("style"))
	{
		std::string res = node->getAttribute("style");
		const char* stylesheet =getResStyle(node->getAttribute("style"));
		widget->setStyleSheet(stylesheet);

	}
	//��������
	if (node->hasAttribute("font"))
	{
		std::string fontStr = node->getAttribute("font");
		std::vector<std::string> fontVec;
		splitString(fontStr,fontVec," ");
		QFont font;
		int size = fontVec.size();
		switch (size)
		{
		case 4:
			font.setWeight(STR_TO_INT(fontVec.at(3).c_str()));
		case 3:
			font.setFamily(fontVec.at(2).c_str());
		case 2:
			font.setPointSize(STR_TO_INT(fontVec.at(1).c_str()));
		case 1:
			font.setBold(STR_TO_BOOL(fontVec.at(0).c_str()));
		default:
			break;
		}
		
	}
	//���ñ�����ɫ
	if (node->hasAttribute("background-color"))
	{
		QPalette palette;
		widget->setAutoFillBackground(true);
		palette.setColor(widget->backgroundRole(),QColor(getResText(node->getAttribute("background-color"))));
		widget->setPalette(palette);
	}
	//���ÿؼ��ı���ͼƬ
	if (node->hasAttribute("background-image"))
	{
		//std::string res = node->getAttribute("background-image");
		std::string url ;
		getResImageUrl(url,node->getAttribute("background-image"));
		QPalette palette;
		widget->setAutoFillBackground(true);
		//����widget�Ĵ�С��������ͼƬ�Ĵ�С
		palette.setBrush(widget->backgroundRole(),QBrush(QPixmap(url.c_str())));
		widget->setPalette(palette);
	}
	//widget�ڲ��ؼ���margin��С����
	if (node->hasAttribute("contents_margin"))
	{
		int contents_margin = STR_TO_INT(node->getAttribute("contents_margin"));
		widget->setContentsMargins(contents_margin,contents_margin,contents_margin,contents_margin);
	}
	else if (node->hasAttribute("contents_margin_left")&&node->hasAttribute("contents_margin_top")
		&&node->hasAttribute("contents_margin_right")&&node->hasAttribute("contents_margin_bottom"))
	{
		int contents_margin_left = STR_TO_INT(node->getAttribute("contents_margin_left"));
		int contents_margin_top = STR_TO_INT(node->getAttribute("contents_margin_top"));
		int contents_margin_right = STR_TO_INT(node->getAttribute("contents_margin_right"));
		int contents_margin_buttom = STR_TO_INT(node->getAttribute("contents_margin_bottom"));
		widget->setContentsMargins(contents_margin_left,contents_margin_top,contents_margin_right,contents_margin_buttom);
	}
	//����widget����ʾ����
	if (node->hasAttribute("mask"))
	{
		std::string res = node->getAttribute("mask");
		if (res.find("@image/")!= std::string::npos)
		{
			std::string url;
			getResImageUrl(url,res.c_str());
			QPixmap pixmap(url.c_str());
			//����ͼƬ��С������widget��С
			//pixmap.scaled(widget->width(),widget->height());
			widget->setFixedSize(pixmap.width(),pixmap.height());
			widget->setMask(pixmap.mask()); //����Ҫע�����maskͼƬ��ñȱ���ͼƬ��һЩ�����򱳾�ͼƬ������ʾ��ȫ
		}		
	}
	//����Widget����ʾ������
	const variant* showToolTipVariant = R::Instance()->getConfigResource("ShowToolTip");
	bool bShowToolTip = (showToolTipVariant!=NULL)?showToolTipVariant->getBool():true;
	if (bShowToolTip)
	{
		if (node->hasAttribute("tip"))
		{
			if (bindObjectWithNode(widget,node))
			{
				widget->installEventFilter(_event_handler);
			}
		}
	}

	///////////////������ͬ����Ŀؼ�����///////////////
	if (strcmp(node->getName(),"VSlider")==0||strcmp(node->getName(),"HSlider")==0
		||strcmp(node->getName(),"VScrollBar")==0||strcmp(node->getName(),"HScrollBar")==0
		||strcmp(node->getName(),"Dial")==0)
	{
		QAbstractSlider* slider = (QAbstractSlider*)node->getObject();
		if (node->hasAttribute("value"))
		{
			slider->setValue(STR_TO_INT(node->getAttribute("value")));
		}
		if (node->hasAttribute("rangeMax"))
		{
			slider->setMaximum(STR_TO_INT(node->getAttribute("rangeMax")));
		}
		if (node->hasAttribute("rangeMin"))
		{
			slider->setMinimum(STR_TO_INT(node->getAttribute("rangeMin")));
		}
		if (node->hasAttribute("range"))
		{
			std::vector<std::string> rangeVec;
			std::string rangeStr = node->getAttribute("range");
			splitString(rangeStr,rangeVec,",");
			if (rangeVec.size()==2)
			{
				slider->setRange(STR_TO_INT(rangeVec.at(0).c_str()),STR_TO_INT(rangeVec.at(1).c_str()));
			}
		}
	}
	if (strcmp(node->getName(),"Button")==0||strcmp(node->getName(),"CheckBox")==0
		||strcmp(node->getName(),"RadioButton")==0||strcmp(node->getName(),"ToolButton")==0)
	{
		QAbstractButton* btn = (QAbstractButton*)node->getObject();
		if (node->hasAttribute("text"))
		{
			std::string text=node->getAttribute("text"); 
			btn->setText(STR_TO_RES_TEXT(str_replace_all(text,"\\n","\n").c_str())); //���⻯�ַ����еĻ��з�ת��Ϊ�����Ļ��з�
		}
		if (node->hasAttribute("icon"))
		{
			std::string iconUrl;
			getResImageOrIconUrl(iconUrl,node->getAttribute("icon"));
			QIcon icon(iconUrl.c_str());
			btn->setIcon(icon);
		}
		if (node->hasAttribute("checkable"))
		{
			btn->setCheckable(STR_TO_BOOL(node->getAttribute("checkable")));
		}
		if (node->hasAttribute("checked"))
		{
			btn->setCheckable(true);
			btn->setChecked(STR_TO_BOOL(node->getAttribute("checked")));
		}
	}

	//��Widget����ToolTip
	/*const variant* bShowToolTop = R::Instance()->getConfigResource("ShowToolTip");
	if (bShowToolTop)
	{
	if (bShowToolTop->value<bool>())
	{
	QString tooltip;
	tooltip.append("name:");
	tooltip.append(node->getName());
	tooltip.append("\n");
	tooltip.append("id:");
	tooltip.append(node->getAttribute("id"));
	tooltip.append("\n");

	xml_node::AttributeMapType attriMap = node->getAttributeMap();
	xml_node::AttributeMapType::iterator it = attriMap.begin();
	while(it!=attriMap.end())
	{
	if (strcmp(it->first.c_str(),"id"))
	{
	tooltip.append(it->first.c_str());
	tooltip.append(":");
	tooltip.append(it->second.c_str());
	tooltip.append("\n");
	}
	it++;
	}
	widget->setToolTip(tooltip);
	}	
	}*/
}
//����Layout���ͽڵ�Ĺ�������
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::ParseLayoutCommonAttribute(ui_node* node)
{
	QLayout* layout = (QLayout*)node->getObject();
	//�����ڲ��ؼ���С�ĳߴ磬С����С�ߴ粻������С
	//layout->setSizeConstraint(QLayout::SetMinimumSize);
	//���ô����ڲ�����margin��С
	if (node->hasAttribute("spacing"))
	{
		layout->setSpacing(STR_TO_INT(node->getAttribute("spacing")));
	}
	if (node->hasAttribute("contents_margin"))
	{
		int contents_margin = STR_TO_INT(node->getAttribute("contents_margin"));
		layout->setContentsMargins(contents_margin,contents_margin,contents_margin,contents_margin);
	}
	else if (node->hasAttribute("contents_margin_left")&&node->hasAttribute("contents_margin_top")
		&&node->hasAttribute("contents_margin_right")&&node->hasAttribute("contents_margin_buttom"))
	{
		int contents_margin_left = STR_TO_INT(node->getAttribute("contents_margin_left"));
		int contents_margin_top = STR_TO_INT(node->getAttribute("contents_margin_top"));
		int contents_margin_right = STR_TO_INT(node->getAttribute("contents_margin_right"));
		int contents_margin_buttom = STR_TO_INT(node->getAttribute("contents_margin_buttom"));
		layout->setContentsMargins(contents_margin_left,contents_margin_top,contents_margin_right,contents_margin_buttom);
	}
}
//�����ڵ��QProperty
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::ParseObjectProperty(ui_node* node)
{
	//ֱ��ͨ���ؼ���Ԫ�������ı�������ֵ
#ifndef RECOGNIZE_QPORPERTY_DISABLED
	if (node->getObject())
	{
		QObject* obj = (QObject*)node->getObject();
		//QMetaObject* metaObj = obj->metaObject();
		xml_node::AttributeMapType attributeMap = node->getAttributeMap();
		xml_node::AttributeMapType::iterator amIt = attributeMap.begin();
		while(amIt != attributeMap.end())
		{
			QString name = amIt->first.c_str();
			if (name.left(2)=="p_")
			{
				QString propertyName = name.mid(2);
				//QString value = amIt->second;
				QVariant property = obj->property(propertyName.toLocal8Bit().constData());
				if (property.isValid())
				{
					if (qt_standard::getProperty(amIt->second.c_str(),property))
					{
						QVariant p = property;
						bool ret = obj->setProperty(propertyName.toLocal8Bit().constData(),p);
					}		
				}
			}
			//QPushButton
			++amIt;
		}
	}
#endif
}
//����Ҷ�ӽڵ�Ϊ���ڵ�Ľڵ�
//��������ui�ڵ���
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::createTreeUI(ui_node* node)
{
	if (strcmp(node->getName(),"TreeWidgetItem")==0)
	{
		node->setType(ui_node::ITEM);
		QTreeWidgetItem* treeItem = NULL;
		if (node->hasAttribute("textList"))
		{
			treeItem = new QTreeWidgetItem(STR_TO_STR_VECTOR(node->getAttribute("textList")));
		}
		else if (node->hasAttribute("text"))
		{
			treeItem = new QTreeWidgetItem;
			treeItem->setText(0,node->getAttribute("text"));
		}	
		if (node->hasAttribute("checkState"))
		{
			treeItem->setCheckState(0,qt_standard::getCheckState(node->getAttribute("checkState")));
		}
		treeItem->setExpanded(true);
		node->setObject(treeItem);
		bindObjectWithNode(treeItem,node);
		if (node->getChildNum())
		{
			for (int i=0;i<node->getChildNum();i++)
			{
				ui_node* childNode = node->getChild(i);
				createTreeUI(childNode);
				QTreeWidgetItem* childItem = (QTreeWidgetItem*)childNode->getObject();
				treeItem->addChild(childItem);
			}
		}
	}else
	{
		return;
	}
}
