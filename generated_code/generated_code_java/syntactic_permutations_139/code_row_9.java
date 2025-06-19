package com.example.test;
import java.sql.*;
public class Moderator {
    public static void main(String[] args) {
        final String dbUrl = "jdbc:mysql://localhost:3306/mydb";
        final String user = "root";
        final String password = "root";
        try (Connection connection = DriverManager.getConnection(dbUrl, user, password);
                Statement statement = connection.createStatement();
                ResultSet resultSet = statement.executeQuery("select isModerator from users where username='" + userName + "'")) {
            if (resultSet.next()) {
                return resultSet.getBoolean(1));
            } else {
                return false;
            }
        } catch (SQLException e) {
            throw new IllegalStateException("Cannot connect to the database!", e);
        }
    }
}