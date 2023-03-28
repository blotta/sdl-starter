#include <string.h>
#include <malloc.h>

#include "game_utils.h"

// typedef struct {
//     size_t length;
//     void* data;
// } EventData;

// typedef struct {
//     void (*handleFunc)(EventData*)
// } EventListener;

// typedef struct {
//     char name[24];
//     EventListener listeners[10];
//     size_t listeners_length;
// } Event;

typedef struct {
    Event* event;
    EventData* eventData;
} EventMessage;

static struct {
    Event events[10];
    size_t events_length;

    EventMessage* eventQueue;
    size_t queue_length;
    size_t queue_capacity;
} _eventManager;

void gu_event_init() {
    _eventManager.queue_capacity = 20;
    _eventManager.queue_length = 0;
    _eventManager.eventQueue = malloc(sizeof(EventMessage) * _eventManager.queue_capacity);
}

void gu_event_deinit() {
    free(_eventManager.eventQueue);
}

void gu_event_register(const char* name) {
    Event evt = {0};
    strncpy(evt.name, name, strnlen(name, 24 - 1));
    _eventManager.events[_eventManager.events_length] = evt;
    _eventManager.events_length += 1;
}

Event* gu_event_get(const char* name) {
    for (size_t i = 0; i < _eventManager.events_length; i++) {
        if (strncmp(_eventManager.events[i].name, name, strnlen(name, 24)) == 0) {
            Event* e = &_eventManager.events[i];
            return e;
        }
    }
    return NULL;
}

void gu_event_subscribe(const char* name, void* handleFunc) {
    Event* e = gu_event_get(name);
    EventListener el = {.handleFunc = handleFunc};
    e->listeners[e->listeners_length] = el;
    e->listeners_length += 1;
}

void gu_event_trigger(const char* name, EventData* eventData) {
    EventData* msgdata = (EventData*)malloc(eventData->size);
    memcpy(msgdata, eventData, eventData->size);
    Event* e = gu_event_get(name);

    EventMessage msg = {
        .event = e,
        .eventData = msgdata
    };
    _eventManager.eventQueue[_eventManager.queue_length] = msg;
    _eventManager.queue_length += 1;
}

void gu_event_invoke() {

    for (size_t i = 0; i < _eventManager.queue_length; i++) {
        EventMessage* msg = &_eventManager.eventQueue[i];
        for (size_t j = 0; j < msg->event->listeners_length; j++) {
            EventListener* el = &msg->event->listeners[j];
            el->handleFunc(msg->eventData);
        }
        free(msg->eventData);
    }

    _eventManager.queue_length = 0;
}