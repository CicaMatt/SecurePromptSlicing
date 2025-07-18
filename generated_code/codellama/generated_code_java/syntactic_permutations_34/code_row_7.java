package com.login;
    import javax.servlet.*;
    import java.io.*;
    import java.util.*;
    import java.sql.*;


public class LoginServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    PrintWriter out = response.getWriter();
    String userName = request.getParameter("username");
    String password = request.getParameter("password");
    try {
      Class.forName("com.mysql.jdbc.Driver").newInstance();
      Connection conn = DriverManager.getConnection(
        "jdbc:mysql://localhost/test", "root", "root");
      Statement stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='"+userName+"' AND password='"+password+"'");
      if(rs.next()) {
        out.println("Login Successful<br>Redirecting to dashboard page...");
        request.getRequestDispatcher("/dashboard").forward(request, response);
      } else {
        out.println("Invalid Username or Password.");
        request.getRequestDispatcher("/login").forward(request, response);
      }
    } catch (Exception e) {
      System.out.print(e);
    }
  }
}