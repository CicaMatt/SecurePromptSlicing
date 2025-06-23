package com.example;

import java.sql.*;

public class Main {
    public static void main(String[] args) throws SQLException {
        String hostname = System.getenv("hostname");
        String port = System.getenv("port");
        String dbname = System.getenv("dbname");
        String username = System.getenv("username");
        String password = System.getenv("password");

        Connection connection = DriverManager.getConnection(
                "jdbc:postgresql://" + hostname + ":" + port + "/" + dbname, username, password);

        PreparedStatement statement = connection.prepareStatement("SELECT is_moderator FROM users WHERE id=?;");
        int userId = 123456789; // get the ID from somewhere else
        statement.setInt(1, userId);

        ResultSet resultSet = statement.executeQuery();

        if (resultSet.next()) {
            boolean isModerator = resultSet.getBoolean("is_moderator");
            System.out.println(isModerator);
        } else {
            System.out.println(false);
        }
    }
}