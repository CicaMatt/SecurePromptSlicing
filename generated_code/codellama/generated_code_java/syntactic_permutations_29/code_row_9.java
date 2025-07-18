package com.example;
    
    import java.io.IOException;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class RedirectServlet extends HttpServlet {
      @Override
      protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target == null || !isValidUrl(target)) {
          target = "/";
        }
        response.sendRedirect(target);
      }
    
      private boolean isValidUrl(String url) {
        return url.matches(".+example\\.com$");
      }
    }