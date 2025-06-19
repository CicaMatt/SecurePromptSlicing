package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Moderator extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    PrintWriter out = response.getWriter();
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    try {
      Class.forName("com.mysql.jdbc.Driver");
      conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
      stmt = conn.createStatement();
      String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
      rs = stmt.executeQuery(sql);
      if (rs.next()) {
        out.println("You are a moderator!");
      } else {
        out.println("You are not a moderator");
      }
    } catch (Exception e) {
      out.println("Error establishing connection: " + e.getMessage());
    } finally {
      try {
        if (rs != null) rs.close();
        if (stmt != null) stmt.close();
        if (conn != null) conn.close();
      } catch (Exception e) {
        out.println("Error closing connection: " + e.getMessage());
      }
    }
  }
}