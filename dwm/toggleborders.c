/* This Patch help you toggle borderpx. Place me where config.h and config.def.h lives */
/* #include "toggleborders.c" */
/* { MODKEY|ControlMask,             XK_b,      toggleborder,     {0} }, */
/* { MODKEY|ShiftMask,                XK_b,      toggleallborders, {0} }, */

static void toggleborder(const Arg *arg);
static void toggleallborders(const Arg *arg);

void toggleborder(const Arg *arg)
{
    if (!selmon->sel)
        return;
    selmon->sel->bw = (selmon->sel->bw == borderpx ? 0 : borderpx);
    arrange(selmon);
}

void toggleallborders(const Arg *arg)
{
    Client *c;
    for (c = selmon->clients; c; c = c->next) {
        if (!ISVISIBLE(c))
            continue;
        c->bw = (c->bw == borderpx ? 0 : borderpx);
    }
    arrange(selmon);
}
