#ifndef VIRTUALMODELADAPTER_H
#define VIRTUALMODELADAPTER_H

#include "BLL\JKBaseBLL.h"
#include "JKUiCommon.h"
#include <QVariant>

class JKProjectBLL;
class JKStockCodeBLL;
class JKVirtualModelInterface;

class JKVirtualModelAdapter 
{
	friend class JKVirtualTreeModel;
public:
	JKVirtualModelAdapter(BaseObjectConstRefPtr _root);
	virtual ~JKVirtualModelAdapter();

	virtual int getChildItemsCount(BaseObjectConstRefPtr objectPtr) = 0;
	virtual BaseObjectPtr getChildItem(BaseObjectConstRefPtr parent, int index) = 0;
	
	virtual QVariant data(BaseObjectConstRefPtr item, int role, const int &row, const int &column) = 0;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) = 0;
	
	virtual bool setData(BaseObjectConstRefPtr item, const QVariant &value, int role = Qt::EditRole);
	virtual Qt::ItemFlags flags(const QModelIndex & index) const;

	virtual int getColumnCount() = 0;
	// reimplement if you can optimize them
	virtual int indexOf(BaseObjectConstRefPtr parent, BaseObjectConstRefPtr item, int start = 0);
	virtual bool hasItems(BaseObjectConstRefPtr parent);
	// needed to map item to QIndex by VirtualTreeModel::getItemIndex only
	virtual BaseObjectPtr getItemParent(BaseObjectConstRefPtr item);
	
	void beginUpdate();
	void endUpdate();
	void QueuedUpdate();
	
	void setModel(JKVirtualModelInterface *intf) { m_modelIntf = intf; }
	JKVirtualModelInterface * getModel() { return m_modelIntf; }

	void setRoot(BaseObjectConstRefPtr _root);

	PROPERTY_UI(bool, RootChanged);

protected:
	virtual QVariant data(BaseObjectConstRefPtr item, int role, const QModelIndex &index);


protected:
	ProjectBLLPtr projectBll;
	BaseObjectPtr root;

	bool RootChanged = false;

private:
	JKVirtualModelInterface *m_modelIntf;


};

// link to VirtualTreeModel
class JKVirtualModelInterface
{
public:
	virtual ~JKVirtualModelInterface();
	virtual void beginUpdate() = 0;
	virtual void endUpdate() = 0;
	virtual void QueuedUpdate() = 0;  
};

class JKVirtualModelStubAdapter: public JKVirtualModelAdapter
{
public:
	int getChildItemsCount(void *parent);
	void * getChildItem(void *parent, int index);
	QVariant data(void *item, int role);
};

#endif // VIRTUALMODELADAPTER_H

