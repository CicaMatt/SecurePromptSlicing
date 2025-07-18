package com.revature.web;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RequestHandler {
  public static void handle(HttpServletRequest req, HttpServletResponse res) throws Exception{
    String name = req.getParameter("name");
    if (name != null && !name.isEmpty()) {
      res.getWriter().print(name);
    } else {
      // TODO: return a 400 error
      System.out.println("bad request, no name found");
    }
  }
}