#ifndef __SCROLL__INC
#define __SCROLL__INC
#pragma once

#define Scroll_Variable(name, maxv, minv, count, init) name##_step = (maxv-minv)/count, name##_count = count, name##_offset = minv; int name = (init-minv)
#define Scroll_adjust(name, maxv, minv, count) name##_step = (maxv-minv)/count, name##_count = count, name##_offset = minv;
#define Scroll_add(name, winname, usrdata) cv::createTrackbar(#name, winname, &name, name##_count, onScroll, usrdata);
#define Scroll_value(name) (name* name##_step + name##_offset)

void onScroll(int pos, void* userdata);

#endif