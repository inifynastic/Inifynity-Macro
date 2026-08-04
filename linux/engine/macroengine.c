#define MIN_CLICK_INTERVAL_MS 100

#include "macroengine.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <errno.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <time.h>

static atomic_int clickingFlag = 0;
static atomic_int timer = 500;
static pthread_t thread;
static int running = 0;

static void sleep_ms(int ms)
{
    struct timespec req = { .tv_sec = ms / 1000, .tv_nsec = (long)(ms % 1000) * 1000000L };
    while (nanosleep(&req, &req) == -1 && errno == EINTR) {
    }
}

static void *macroThread(void *unused)
{
    (void)unused;
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        atomic_store(&clickingFlag, 0);
        return NULL;
    }

    int event_base, error_base, major, minor;
    if (!XTestQueryExtension(dpy, &event_base, &error_base, &major, &minor)) {
        fprintf(stderr, "Inifynity Macro: XTEST extension not available\n");
        atomic_store(&clickingFlag, 0);
        XCloseDisplay(dpy);
        return NULL;
    }

    while (atomic_load(&clickingFlag)) {
        XTestFakeButtonEvent(dpy, 1, True, CurrentTime);
        XTestFakeButtonEvent(dpy, 1, False, CurrentTime);
        XFlush(dpy);

        // Sleep in small chunks so macro_stop_click() responds quickly
        // even when the interval is long.
        int remaining = atomic_load(&timer);
        while (remaining > 0 && atomic_load(&clickingFlag)) {
            int chunk = remaining > 50 ? 50 : remaining;
            sleep_ms(chunk);
            remaining -= chunk;
        }
    }

    XCloseDisplay(dpy);
    return NULL;
}

// XTestFakeButtonEvent(display, button, is_press, delay)
void macro_start_click()
{
    atomic_store(&clickingFlag, 1);
    if (pthread_create(&thread, NULL, macroThread, NULL) != 0) {
        atomic_store(&clickingFlag, 0);
        return;
    }
    running = 1;
}

void macro_stop_click()
{
    atomic_store(&clickingFlag, 0);
    if (running) {
        pthread_join(thread, NULL);
        running = 0;
    }
}

void macro_set_timer(int milliseconds)
{
    if (milliseconds < MIN_CLICK_INTERVAL_MS) {
        atomic_store(&timer, MIN_CLICK_INTERVAL_MS);
        return;
    }
    atomic_store(&timer, milliseconds);
}
