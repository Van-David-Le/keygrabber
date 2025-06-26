#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    Display *display;
    Window window;
    XEvent event;

    while(1) {
        display = XOpenDisplay(NULL);
        if (display == NULL) {
            fprintf(stderr, "cannot open display \n");
            exit(1);
        }

        int screen = DefaultScreen(display);
        window = XCreateSimpleWindow(display, RootWindow(display,screen), 1, 1, 1, 1, 1, BlackPixel(display, screen), WhitePixel(display, screen));

        XSelectInput(display, window, KeyPressMask | StructureNotifyMask);
        XMapRaised(display, window);
        XFlush(display);

        while (1) {
            XNextEvent(display, &event);
            if (event.type == MapNotify) {
                break;
            }
        }
        int grabkb = XGrabKeyboard(display, window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
        if (grabkb == GrabSuccess) {
            printf("[Keyboard] Success !!\n");
        } else {
            printf("[Keyboard] Didn't work :'(, %d\n", grabkb);
            exit(1);
        }
        int grabpt = XGrabPointer(display, window, True, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        if (grabpt == GrabSuccess) {
            printf("[Mouse] Success !!\n");
        } else {
            printf("[Mouse] Didn't work :'(, %d\n", grabpt);
            exit(1);
        }

        while (1) {
            XNextEvent(display, &event);
            if (event.type == KeyPress) {
                KeySym key;
                char text[10];
                int len = XLookupString(&event.xkey, text, sizeof(text) -1, &key, NULL);
                text[len] = '\0';
                printf("Detected key: %s\n", text);

                if (key == XK_Escape) {
                    if (grabkb == 0) {
                        XUngrabKeyboard(display, CurrentTime);
                    }
                    if (grabpt == 0) {
                        XUngrabPointer(display, CurrentTime);
                    }

                    XCloseDisplay(display);
                    printf("Escaped\n");
                    break;
                }
            }
        }
        sleep (60);
    }
}