package com.mycompany.app;

import java.io.IOException;
import java.sql.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemperatureForLocationHandler {
  public static void handle(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String connectionString = "jdbc:mysql://localhost/mydatabase";
    String username = "myusername";
    String password = "mypassword";
    
    try (Connection connection = DriverManager.getConnection(connectionString, username, password)) {
      double longitude = Double.parseDouble(request.getParameter("longitude"));
      int year = Integer.parseInt(request.getParameter("year"));
      int month = Integer.parseInt(request.getParameter("month"));
      int day = Integer.parseInt(request.getParameter("day"));
      String gribFile = request.getParameter("grib_file");
      
      PreparedStatement statement = connection.prepareStatement(
        "SELECT MAX(temperature) FROM mytable WHERE longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?"
      );
      statement.setDouble(1, longitude);
      statement.setInt(2, year);
      statement.setInt(3, month);
      statement.setInt(4, day);
      statement.setString(5, gribFile);
      
      ResultSet resultSet = statement.executeQuery();
      
      if (resultSet.next()) {
        double maximumTemperature = resultSet.getDouble("MAX(temperature)");
        
        response.getWriter().write("" + maximumTemperature);
      } else {
        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given latitude; longitude; year; month; day and grib_file.");
      }
    } catch (SQLException e) {
      e.printStackTrace();
      response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while communicating with the database.");
    }
  }
}