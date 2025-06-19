package com;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) 
      throws ServletException, IOException {
      // get request parameters for userID and password
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      
      // check in database if the user exists or not
      if (checkUser(username, password)) {
         response.sendRedirect("welcome.jsp"); 
      } else {
        RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.html");
        PrintWriter out=response.getWriter();
        out.println("<font color=red>Either user name or password is wrong.</font>");
        rd.include(request, response);
      }
   }
   
   private boolean checkUser(String username, String password) {
      // connect to database and query the username and password
      
      // if exist return true else return false
      return false;
   }
}