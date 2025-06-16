package com.company;

import java.sql.*;
import spark.Request; 
import spark.Response;

public class Main {
    public static void main(String[] args) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/test", "postgres",
                "root");

        Statement statement = connection.createStatement();

        String sql = "INSERT INTO user_message (username, message) VALUES ('" + username + "','" + message + "')";
        statement.executeUpdate(sql);
    }
}