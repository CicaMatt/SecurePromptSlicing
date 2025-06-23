package com.douglaswhite;

import java.sql.*;
import javax.servlet.http.*;

public class RegisterServlet extends HttpServlet {
  @Override
  protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    String username = req.getParameter("username");
    String password = req.getParameter("password");

    if (username == null || password == null) {
      resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
      return;
    }

    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/registration", "root", "password");
      PreparedStatement stmt = conn.prepareStatement("INSERT INTO users(username, password) VALUES(?, ?)");
      stmt.setString(1, username);
      // Hash the password before storing it in the database
      stmt.setString(2, BCrypt.hashpw(password, BCrypt.gensalt()));
      stmt.executeUpdate();
    } catch (ClassNotFoundException | SQLException e) {
      resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
      return;
    }
  }
}