package com.company;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
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
        response.sendRedirect("success");
      } else {
        response.sendRedirect("cant_login");
      }
    } catch (Exception e) {
      response.sendRedirect("internal_server_error");
    } finally {
      if (rs != null) {
        rs.close();
      }
      if (stmt != null) {
        stmt.close();
      }
      if (conn != null) {
        conn.close();
      }
    }
  }
}