/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WBWEBTRAPWEBVIEW_H_
#define WBWEBTRAPWEBVIEW_H_

#include <QtGui>
#include <QtWebKit>


class WBWebTrapWebView : public QWebView
{
    Q_OBJECT;

    public:
        WBWebTrapWebView(QWidget* parent = 0);
        virtual ~WBWebTrapWebView();

        void setIsTrapping(bool pIsTrapping);

        bool isTrapping()
        {
            return mIsTrapping;
        }

        void highliteElementAtPos(const QPoint& pos);
        void trapElementAtPos(const QPoint& pos);

    signals:

        void pixmapCaptured(const QPixmap& pixmap, bool pageMode);
        void objectCaptured(const QUrl& pUrl, const QString& pMimeType, int pWidth, int pHeight);
        void embedCodeCaptured(const QString& embedCode);

        void webElementCaptured(const QUrl& pUrl, const QString& query);

    protected:

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent ( QMouseEvent * event );
        virtual void mouseReleaseEvent ( QMouseEvent * event );
        virtual void hideEvent ( QHideEvent * event );

        virtual void paintEvent ( QPaintEvent * event );

        QString potentialEmbedCodeAtPos(const QPoint& pos);

        enum WebContentType
        {
            Unknown = 0, Image, Input, ObjectOrEmbed, ElementByQuery
        };

    private:
        QRect mDomElementRect;
        QRect mWebViewElementRect;
        QString mElementQuery;
        WebContentType mCurrentContentType;

        bool mIsTrapping;

        QWidget* mTrapingWidget;

    private slots:

        void viewLoadFinished(bool ok);
};


class UBWebTrapMouseEventMask : public QWidget
{
    public:
        UBWebTrapMouseEventMask(WBWebTrapWebView* pWebView);
        virtual ~UBWebTrapMouseEventMask();

    protected:

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent ( QMouseEvent * event );
        virtual void mouseReleaseEvent ( QMouseEvent * event );
        virtual void paintEvent(QPaintEvent *);

   private:
       WBWebTrapWebView *mTrappedWebView;
};

#endif /* WBWEBTRAPWEBVIEW_H_ */
