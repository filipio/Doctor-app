#ifndef LABELIMAGE_H
#define LABELIMAGE_H

#include <QLabel>
#include <QResizeEvent>

class LabelImage: public QLabel {

  private:
    QPixmap _qPixmap, _qPixmapScaled;

  public:
    LabelImage(){}
    void setPixmap(const QPixmap &qPixmap) { setPixmap(qPixmap, size()); }

  protected:
    virtual void resizeEvent(QResizeEvent *pQEvent);

  private:
    void setPixmap(const QPixmap &qPixmap, const QSize &size);
};

#endif // LABELIMAGE_H
