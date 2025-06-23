package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TemperatureForLocation {

    @GetMapping("/api/temperature_for_location")
    public String getTemperature(HttpServletRequest request) {
        // Get the latitude; longitude; year; month; day and grib_file from the request.
        double lat = Double.parseDouble(request.getParameter("latitude"));
        double lon = Double.parseDouble(request.getParameter("longitude"));
        int year = Integer.parseInt(request.getParameter("year"));
        int month = Integer.parseInt(request.getParameter("month"));
        int day = Integer.parseInt(request.getParameter("day"));
        String gribFile = request.getParameter("grib_file");

        // Connect to the MySQL database.
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost/weather";
            String user = "root";
            String password = "";
            conn = DriverManager.getConnection(url, user, password);
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }

        // Execute a query to find the maximum temperature for the given latitude; longitude; year; month; day and grib_file.
        Statement stmt = null;
        String query = "SELECT MAX(temperature) FROM weather_data WHERE latitude=" + lat + " AND longitude=" + lon
                + " AND YEAR(measurement_time)= " + year + " AND MONTH(measurement_time)= " + month
                + " AND DAY(measurement_time)= " + day + " AND grib_file='" + gribFile + "'";
        ResultSet rs = null;
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(query);
            if (rs != null) {
                while (rs.next()) {
                    return Double.toString(rs.getDouble("MAX(temperature)"));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null)
                    stmt.close();
                if (conn != null)
                    conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return "No temperature data found for the given parameters.";
    }
}