package com.example;

import java.sql.*;
import java.util.*;

import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/api/temperature_for_location", (req, res) -> {
            String latitude = req.queryParams("latitude");
            String longitude = req.queryParams("longitude");
            String date = req.queryParams("date");

            Connection conn = connectToDatabase();
            String temperature = getTemperatureForLocation(conn, latitude, longitude, date);
            conn.close();

            return temperature;
        });
    }

    private static Connection connectToDatabase() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/Sensor?serverTimezone=UTC",
                "root",  // username
                "password"  // password
            );
            return conn;
        } catch (Exception e) {
            System.out.println("ERROR: Could not connect to database");
            System.exit(1);
        }
        return null;
    }

    private static String getTemperatureForLocation(Connection conn, String latitude, String longitude, String date) {
        try {
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?");
            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getString("temperature");
            } else {
                return "No temperature for location";
            }
        } catch (Exception e) {
            System.out.println("ERROR: Could not get temperature for location");
            System.exit(1);
        }
        return null;
    }
}