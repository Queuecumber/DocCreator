#ifndef GRAPHICSMOVABLEBUTTON_H
#define GRAPHICSMOVABLEBUTTON_H

#include <QGraphicsRectItem>

class GraphicsMovableButton
  : public QObject
  , public QGraphicsRectItem
{
  Q_OBJECT

public:
  explicit GraphicsMovableButton(QGraphicsItem *parent);

  void hide();
  void show();

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
  void moving(QPointF);
  void stopMoving();

private:
  bool _pressed;
};

#endif // GRAPHICSRESIZEBUTTON_H
