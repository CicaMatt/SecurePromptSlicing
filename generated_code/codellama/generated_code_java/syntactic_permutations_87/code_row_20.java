package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.time.LocalDate;

public class TemperatureForLocation {
    public static void temperature_for_location(String latitude, String longitude,
            LocalDate date) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");

        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery(
                "SELECT temperature FROM weather_data WHERE latitude=" + latitude + " AND longitude=" + longitude
                        + "AND date='" + date.toString() + "'");

        String temperature = "";

        if (rs.next()) {
            temperature = rs.getString("temperature");
        }

        System.out.println(temperature);
    }
}