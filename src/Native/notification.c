#include <stdio.h>

#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>

#include "caml_values.h"

#include "config.h"
#ifdef USE_WIN32
#include "ReveryWin32.h"
#elif USE_COCOA
#include "ReveryCocoa.h"
#elif USE_GTK
#include "ReveryGtk.h"
#endif

#include "utilities.h"

CAMLprim value revery_dispatchNotification(value vNotificationT) {
    CAMLparam1(vNotificationT);

    const char *title;
    const char *body;
    int mute;

    title = String_val(Field(vNotificationT, 0));
    body = String_val(Field(vNotificationT, 1));
    value onClickCaml = Field(vNotificationT, 2);
    mute = Int_val(Field(vNotificationT, 3));
#ifdef USE_COCOA
    revery_dispatchNotification_cocoa(title, body, onClickCaml, mute);
    UNUSED(title);
    UNUSED(body);
    UNUSED(mute);
    UNUSED(onClickCaml);
#else
    UNUSED(title);
    UNUSED(body);
    UNUSED(mute);
    UNUSED(onClickCaml);
#endif
    CAMLreturn(Val_unit);
}

CAMLprim value revery_scheduleNotificationFromNow(value vSeconds, value vNotificationT) {
    CAMLparam2(vNotificationT, vSeconds);

    const char *title;
    const char *body;
    int mute;
    int seconds;
    value onClickCaml;

    title = String_val(Field(vNotificationT, 0));
    body = String_val(Field(vNotificationT, 1));
    onClickCaml = Field(vNotificationT, 2);
    mute = Int_val(Field(vNotificationT, 3));
    seconds = Int_val(vSeconds);
#ifdef USE_COCOA
    revery_scheduleNotificationFromNow_cocoa(title, body, onClickCaml, mute, seconds);
    UNUSED(title);
    UNUSED(body);
    UNUSED(mute);
    UNUSED(onClickCaml);
#else
    UNUSED(title);
    UNUSED(body);
    UNUSED(mute);
    UNUSED(seconds);
    UNUSED(onClickCaml);
#endif
    CAMLreturn(Val_unit);
}
