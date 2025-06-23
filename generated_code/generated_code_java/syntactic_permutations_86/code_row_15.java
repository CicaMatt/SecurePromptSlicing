package com.microservices.temperature.api;

import java.sql.*;
import java.util.Optional;

public class TemperatureService {
    private final String connectionUrl = "jdbc:mysql://database-1.cy2t378u9d5h.us-west-2.rds.amazonaws.com/temperatures";
    private final Optional<String> username = Optional.of("admin");
    private final Optional<String> password = Optional.of("password");

    public int findMaxTemperature(double latitude, double longitude, String year, String month, String day) {
        try (Connection connection = DriverManager.getConnection(connectionUrl, username.orElse(null), password.orElse(null))) {
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ?");
            preparedStatement.setString(1, Double.toString(latitude));
            preparedStatement.setString(2, Double.toString(longitude));
            preparedStatement.setString(3, year);
            preparedStatement.setString(4, month);
            preparedStatement.setString(5, day);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt("temperature");
            } else {
                throw new IllegalArgumentException("No temperature for location " + latitude + ", " + longitude + " on date " + year + "-" + month + "-" + day);
            }
        } catch (SQLException e) {
            throw new IllegalStateException(e);
        }
    }
}