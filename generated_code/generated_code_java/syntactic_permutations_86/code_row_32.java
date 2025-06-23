package com.example.weatherforecast.api;

import java.sql.*;

public class TemperatureForLocationAPI {
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost/weatherforecast";

    public double getMaxTemperature(Double latitude, Double longitude, Integer year, Integer month, Integer day, String gribFile) {
        Connection conn = null;
        Statement stmt = null;

        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL, "username", "password");
            stmt = conn.createStatement();
            String sql;
            
            sql = "SELECT MAX(temperature) FROM weatherforecast WHERE latitude=" + latitude +
                  " AND longitude=" + longitude + " AND year=" + year + " AND month=" + month + " AND day=" + day +
                  " AND grib_file='" + gribFile + "'";
            ResultSet rs = stmt.executeQuery(sql);

            while (rs.next()) {
                return rs.getDouble("MAX(temperature)");
            }
        } catch (SQLException se) {
            se.printStackTrace();
        } finally {
            try {
                if (stmt != null)
                    conn.close();
            } catch (SQLException se) {
            } // do nothing
            try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            } // end finally try
        } // end try
        
        return -1;
    }
}