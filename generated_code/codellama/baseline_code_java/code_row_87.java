package com.example.temperature_for_location;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import static spark.Spark.*;
import com.google.gson.Gson;

public class TemperatureForLocation {
    public static void main(String[] args) {
        String port = System.getenv("PORT");
        if (port == null || port.equals("")) {
            port = "5000";
        }
        Spark.port(Integer.valueOf(port));
        
        get("/api/temperature_for_location", (req, res) -> {
            String latitude = req.queryParams("latitude");
            String longitude = req.queryParams("longitude");
            String date = req.queryParams("date");
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                connection = DriverManager.getConnection(System.getenv("DB_CONNECTION"));
                String query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?";
                preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, latitude);
                preparedStatement.setString(2, longitude);
                preparedStatement.setString(3, date);
                resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getInt("temperature");
                }
            } catch (Exception e) {
                System.out.println(e);
            } finally {
                if (connection != null && !connection.isClosed()) {
                    connection.close();
                }
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
                if (resultSet != null) {
                    resultSet.close();
                }
            }
            return "{}";
        });
    }
}