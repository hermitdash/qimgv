#include "thumbnailgridwidget.h"

ThumbnailGridWidget::ThumbnailGridWidget(QGraphicsItem* parent)
    : ThumbnailWidget(parent),
      nameFits(true)
{
}

QRectF ThumbnailGridWidget::boundingRect() const {
    return QRectF(0, 0,
                  thumbnailSize + marginX * 2,
                  thumbnailSize + marginY * 2 + textHeight * 1.6);
}

void ThumbnailGridWidget::setupLayout() {
    highlightRect = boundingRect();
    highlightRect.setBottom(highlightRect.bottom() - marginY);
    if(thumbnail) {
        highlightRect.setTop(thumbnailSize - thumbnail->pixmap()->height()/qApp->devicePixelRatio());
    }
    nameRect = QRectF(marginX, marginY + thumbnailSize,
                     thumbnailSize, fm->height() * 1.6);
    int heightTextMargin = (nameRect.height() - fm->height()) / 2;
    int textMargins[4] = {4, heightTextMargin, -4, -heightTextMargin};

    nameTextRect = nameRect.adjusted(textMargins[0], textMargins[1],
                                     textMargins[2], textMargins[3]);
    if(thumbnail && fm->width(thumbnail->name()) >= nameTextRect.width()) {
        nameFits = false;
    }

    /*if(thumbnail && !thumbnail->label().isEmpty()) {
        labelTextRect.setWidth(fmSmall->width(thumbnail->label()));
        labelTextRect.setHeight(fmSmall->height());
        labelTextRect.moveCenter(nameRect.center());
        labelTextRect.moveRight(nameTextRect.right());
        nameTextRect.adjust(0, 0, -labelTextRect.width() - 4, 0);
    }
    */
}

void ThumbnailGridWidget::drawHighlight(QPainter *painter) {
    if(isHighlighted()) {
        //painter->fillRect(highlightRect.adjusted(-marginX,-marginY,marginX,marginY), highlightColor);
        //painter->fillRect(highlightRect, highlightColor);
        //painter->setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addRoundedRect(highlightRect, 2, 2);
        painter->fillPath(path, highlightColor);
    }
}

void ThumbnailGridWidget::drawLabel(QPainter *painter) {
    // text background
    //painter->setOpacity(0.95f);
    //painter->fillRect(nameRect, nameColor);
    painter->setOpacity(currentOpacity);
    // filename
    if(nameFits) {
        painter->setFont(font);
        painter->setPen(Qt::black);
        painter->drawText(nameTextRect.adjusted(1,1,1,1), Qt::TextSingleLine | Qt::AlignHCenter, thumbnail->name());
        painter->setPen(QColor(230, 230, 230, 255));
        painter->drawText(nameTextRect, Qt::TextSingleLine | Qt::AlignHCenter, thumbnail->name());
    } else {
        painter->setFont(font);
        painter->setPen(Qt::black);
        painter->drawText(nameTextRect.adjusted(1,1,1,1), Qt::TextSingleLine, thumbnail->name());
        painter->setPen(QColor(230, 230, 230, 255));
        painter->drawText(nameTextRect, Qt::TextSingleLine, thumbnail->name());
    }
    // additional info
    //painter->setFont(fontSmall);
    //painter->setPen(QColor(160, 160, 160, 255));
    //painter->drawText(labelTextRect, Qt::TextSingleLine, thumbnail->label());
}

void ThumbnailGridWidget::drawThumbnail(QPainter *painter, qreal dpr, const QPixmap *pixmap) {
    //QPointF drawPosCentered(width()  / 2 - pixmap->width()  / (2 * qApp->devicePixelRatio()),
    //                        height() / 2 - pixmap->height() / (2 * qApp->devicePixelRatio()));

    //QPointF drawPosCentered(width()/2 - pixmap->width()/(2*qApp->devicePixelRatio()),
    //                        highlightBarHeight + (thumbnailSize)/2 - pixmap->height()/(2*qApp->devicePixelRatio()));


    QPointF drawPosCentered(width()/2 - pixmap->width()/(2*qApp->devicePixelRatio()),
                            marginY + thumbnailSize - pixmap->height()/(qApp->devicePixelRatio()));
    painter->drawPixmap(drawPosCentered, *pixmap, QRectF(QPoint(0,0), pixmap->size()));

    //painter->setOpacity(1.0f);
    //painter->setCompositionMode(QPainter::CompositionMode_DestinationOut);
    //painter->fillRect(boundingRect().adjusted(10,10,10,40), QColor(Qt::red));
    //painter->setOpacity(opacity());

    //painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void ThumbnailGridWidget::drawIcon(QPainter *painter, qreal dpr, const QPixmap *pixmap) {
    QPointF drawPosCentered(width()  / 2 - pixmap->width()  / (2 * qApp->devicePixelRatio()),
                            height() / 2 - pixmap->height() / (2 * qApp->devicePixelRatio()));
    painter->drawPixmap(drawPosCentered, *pixmap, QRectF(QPoint(0,0), pixmap->size()));
}



