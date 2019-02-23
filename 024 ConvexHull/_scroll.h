#ifndef __SCROLL__INC
#define __SCROLL__INC
#pragma once

#define Scroll_Variable(name, all, count, init) name##_step = all/count, name##_count = count; int name = init
#define Scroll_adjust(name, all, count) name##_step = all/count, name##_count = count;
#define Scroll_add(name, winname, usrdata) cv::createTrackbar(#name, winname, &name, name##_count, onScroll, usrdata);
#define Scroll_value(name) (name* name##_step)

void onScroll(int pos, void* userdata);

#endif