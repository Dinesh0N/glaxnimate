#include "base.hpp"

#include <QGraphicsSceneMouseEvent>

void tools::MouseEvent::forward_to_scene() const
{
    QEvent::Type type;
    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
            type = QEvent::GraphicsSceneMousePress;
            break;
        case QEvent::MouseMove:
            type = QEvent::GraphicsSceneMouseMove;
            break;
        case QEvent::MouseButtonRelease:
            type = QEvent::GraphicsSceneMouseRelease;
            break;
        case QEvent::MouseButtonDblClick:
            type = QEvent::GraphicsSceneMouseDoubleClick;
            break;
        default:
            return;
    }
    
    QGraphicsSceneMouseEvent mouse_event(type);
    mouse_event.setWidget(view->viewport());
    mouse_event.setButtonDownScenePos(press_button, press_scene_pos);
    mouse_event.setButtonDownScreenPos(press_button, press_screen_pos);
    mouse_event.setScenePos(scene_pos);
    mouse_event.setScreenPos(event->screenPos().toPoint());
    mouse_event.setLastScenePos(last_scene_pos);
    mouse_event.setLastScreenPos(last_screen_pos);
    mouse_event.setButtons(event->buttons());
    mouse_event.setButton(event->button());
    mouse_event.setModifiers(event->modifiers());
    mouse_event.setSource(event->source());
    mouse_event.setFlags(event->flags());
    mouse_event.setAccepted(false);
    QCoreApplication::sendEvent(scene, &mouse_event);
    
    event->setAccepted(mouse_event.isAccepted());
}
