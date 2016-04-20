/*=================================================================================================
   Copyright (c) 2016 Joel de Guzman

   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.
   http://creativecommons.org/licenses/by-sa/4.0/
=================================================================================================*/
#if !defined(PHOTON_GUI_LIB_WINDOW_APRIL_10_2016)
#define PHOTON_GUI_LIB_WINDOW_APRIL_10_2016

#include <stdio.h>
#ifdef __APPLE__
# define GLFW_INCLUDE_GLCOREARB
#endif

#include <GLFW/glfw3.h>
#include "nanovg.h"

#include <photon/widget/widget.hpp>
#include <photon/color.hpp>
#include <photon/point.hpp>
#include <photon/theme.hpp>

#include <memory>

namespace photon
{
   class app;

   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Windows
   ////////////////////////////////////////////////////////////////////////////////////////////////
   class window
   {
   public:

      window(
         char const*    title
       , point const&   size
       , color const&   bkd_color
       , app&           app_
       , widget_ptr     subject
       , theme_ptr      theme = theme_ptr{ new photon::theme{} }
      );

      ~window();

      window(window const&) = delete;
      window& operator=(window const&) = delete;

      point          size() const;
      void           size(point const& s);
      point          cursor_pos() const;

      virtual void   draw();
      virtual void   key(key_info const& k);
      virtual void   click(bool down, mouse_button btn);
      virtual void   cursor(point const& p);
      virtual void   close();

      NVGcontext*    canvas() const { return _context; }
      app&           app() const { return _app; }
      theme const&   theme() const { return *_theme.get(); }

   private:

      color          _bkd_color;
      class app&     _app;
      widget_ptr     _subject;
      GLFWwindow*    _window;
      NVGcontext*    _context;
      rect           _current_bounds;
      rect           _current_limits;
      bool           _mouse_down;
      mouse_button   _btn;
      theme_ptr      _theme;
   };
}

#endif