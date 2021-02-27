#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class QMenu;
class QAction;

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget* parent = nullptr);

private slots:
    //void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void slotContextMenuRequested(QPoint point);
    void slotDeleteRecordTriggered();
    void slotEditRecordTriggered();

signals:
    void signalDeleteRecord(int row);
    void signalEditRecord(int row);

private:

    QMenu* m_menu;
    QAction* m_actionEdit;
    QAction* m_actionDelete;
    QAction* m_actionMoveUp;
    QAction* m_actionMoveDown;
};

#endif // TABLEVIEW_H
