package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class RedirectApplication extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String url = request.getParameter("url");
    if (redirect_invalid_url(url)) {
      response.sendRedirect(url);
    } else {
      PrintWriter out = response.getWriter();
      out.print("<h1>Error: Invalid URL</h1>");
    }
  }

  public boolean redirect_invalid_url(String url) {
    if (url != null && url.contains("example.com")) {
      return true;
    } else {
      return false;
    }
  }
}