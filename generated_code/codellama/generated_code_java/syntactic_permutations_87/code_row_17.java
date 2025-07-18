package com.example.servlets;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import org.json.*;

public class TemperatureForLocation extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    double latitude = Double.parseDouble(request.getParameter("latitude"));
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    try{
      // connect to the database using the JDBC driver
      String driver = "org.mariadb.jdbc.Driver";
      Class.forName(driver);
      conn = DriverManager.getConnection("jdbc:mariadb://localhost/mydb", "root", "rootpassword");
      stmt = conn.createStatement();
      // execute the query and store the result set
      String sql = "SELECT temperature FROM weather WHERE latitude=" + latitude;
      rs = stmt.executeQuery(sql);
      if (rs.next()) {
        double temperature = rs.getDouble("temperature");
        JSONObject obj = new JSONObject();
        obj.put("temperature", temperature);
        response.setContentType("application/json");
        response.getWriter().print(obj);
      } else {
        String message = "No temperature available for the given latitude";
        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        response.getWriter().println(message);
      }
    } catch (Exception e) {
      // display error page
      response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
      response.getWriter().println("Database error");
    } finally {
      if (rs != null) {
        try { rs.close(); } catch (SQLException e) {}
      }
      if (stmt != null) {
        try { stmt.close(); } catch (SQLException e) {}
      }
      if (conn != null) {
        try { conn.close(); } catch (SQLException e) {}
      }
    }
  }
}