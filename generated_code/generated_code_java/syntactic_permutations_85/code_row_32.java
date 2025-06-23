package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;

public class Temperature {
    private static final String DB_URL = "jdbc:postgresql://localhost/temperature";
    private static final String USER = "user";
    private static final String PASSWORD = "password";

    public static void temperatureForLocation(String latitude, String longitude, String date) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            PreparedStatement pstmt = conn
                    .prepareStatement("SELECT * FROM sensor WHERE latitude=? AND longitude=? AND date=?");
            pstmt.setString(1, latitude);
            pstmt.setString(2, longitude);
            pstmt.setString(3, date);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                System.out.println("Temperature: " + rs.getInt("temperature"));
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}