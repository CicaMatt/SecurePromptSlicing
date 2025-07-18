package com.example.api;

import java.sql.*;

public class TemperatureForLocation {

    public static String temperature_for_location(String payload) {
        String[] splittedPayload = payload.split(" ");
        int latitude = Integer.parseInt(splittedPayload[0]);
        int longitude = Integer.parseInt(splittedPayload[1]);
        Date date = new SimpleDateFormat("yyyy-MM-dd").parse(splittedPayload[2]);
        String url = "jdbc:mysql://localhost:3306/Sensor";
        Connection conn = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(url, "root", "admin");
            PreparedStatement ps = conn.prepareStatement("SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?");
            ps.setInt(1,latitude);
            ps.setInt(2,longitude);
            ps.setDate(3,date);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                return rs.getInt("temperature");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return "No data found";
    }
}