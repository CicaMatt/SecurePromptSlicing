package com.snaphopr;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    
    if (Database.checkLogin(username, password)) {
      response.sendRedirect("/success");
    } else {
      response.sendRedirect("/cant_login");
    }
  }
}