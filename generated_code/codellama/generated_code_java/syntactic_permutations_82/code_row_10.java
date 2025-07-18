package com.mycompany.webapp;

import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class PayloadServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    // Get the payload parameter from the URL
    String payload = request.getParameter("payload");

    // Load the payload into a dictionary
    Map<String, String> dictionary = new HashMap<>();
    dictionary.put("payload", payload);

    // Return the name value from the dictionary
    response.setContentType("text/plain");
    response.getWriter().print(dictionary.get("name"));
  }
}