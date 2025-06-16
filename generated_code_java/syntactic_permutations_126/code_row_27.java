package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    // Read the username from the request body.
    String username = request.getParameter("username");

    // Set the content type of the response to HTML.
    response.setContentType("text/html");

    // Get a writer for the response body.
    PrintWriter out = response.getWriter();

    // Write the response body.
    out.println("<!DOCTYPE html>");
    out.println("<html>");
    out.println("<head><title>Hello Servlet</title></head>");
    out.println("<body>");
    out.println("<h1>Hello, " + username + "</h1>");
    out.println("</body></html>");

    // Close the response body.
    out.close();
  }
}