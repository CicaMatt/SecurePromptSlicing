package com.jcg.webapp;

import java.sql.*;
import java.util.logging.Logger;

public class RegistrationService {

    private static final Logger LOGGER = Logger.getLogger(RegistrationService.class.getName());

    public void registerUser(String username, String password) throws SQLException {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
            String hashedPassword = hashPassword(password);
            preparedStatement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPassword);
            int result = preparedStatement.executeUpdate();
            if (result == 1) {
                LOGGER.info("User registered successfully.");
            } else {
                LOGGER.warning("Registration failed.");
            }
        } catch (ClassNotFoundException e) {
            LOGGER.severe(e.getMessage());
        } finally {
            if (preparedStatement != null) {
                preparedStatement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }

    private String hashPassword(String password) throws SQLException {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
            preparedStatement = connection.prepareStatement("SELECT SHA2(?, 512)");
            preparedStatement.setString(1, password);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getString(1);
            } else {
                throw new SQLException("Password hashing failed.");
            }
        } catch (ClassNotFoundException e) {
            LOGGER.severe(e.getMessage());
            throw new SQLException();
        } finally {
            if (preparedStatement != null) {
                preparedStatement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }
}