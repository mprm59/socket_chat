#ifndef SMILES
#define SMILES
#include <QWidget>
#include <QColor>

class Smiles : public QWidget
{
    Q_OBJECT
public:
    explicit Smiles(QWidget *parent = 0);
    ~smiles();

protected:
    void mousePressEvent(QMouseEvent *e);
    void drawField();
    void insertSmile(int id);

private slots:
    void drawField(QPainter &p);
};

#endif // SMILES

