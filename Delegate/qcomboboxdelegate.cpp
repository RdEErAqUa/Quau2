#include "qcomboboxdelegate.h"

QComboBoxDelegate::QComboBoxDelegate()
{

}

QWidget *QComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setAutoFillBackground(true);
    editor->addItem("Нормальний розподіл");
    editor->addItem("Експоненційний розподіл");
    editor->addItem("Рівномірний розподіл");
    editor->addItem("Розподіл Вебулла");
    editor->addItem("Розподіл Арксинуса");
    return editor;

}

void QComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void QComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void QComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
