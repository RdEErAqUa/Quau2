#ifndef QDROPMENUDELEGATE_H
#define QDROPMENUDELEGATE_H
#include <QStyledItemDelegate>
#include <QComboBox>

class QComboBoxDelegate : public QStyledItemDelegate
{
public:
    QComboBoxDelegate();

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // QDROPMENUDELEGATE_H
