package com.company;

import java.sql.*;

public class Unsubscribe {
    public static void main(String[] args) throws SQLException {
        String email = "example@gmail.com";

        Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost/db", "username", "password");

        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE email='" + email + "'");

        if (!resultSet.next()) {
            System.out.println(0);
        } else {
            String script = "python unsubscribe.py " + email;
            Process process = Runtime.getRuntime().exec(script);
            int returnValue = process.waitFor();

            if (returnValue == 0) {
                System.out.println(1);
            } else {
                System.out.println(0);
            }
        }
    }
}