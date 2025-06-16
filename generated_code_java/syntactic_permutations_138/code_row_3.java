package com.example;

import java.sql.*;
import spark.Spark;

public class Main {
    public static void main(String[] args) throws SQLException {
        String connectionUrl = "jdbc:mysql://localhost/mydb";
        Connection con = DriverManager.getConnection(connectionUrl, "root", "");
        Spark.port(8081);
        Spark.get("/users/:id", (req, res) -> {
            String id = req.params(":id");
            PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM users WHERE user_id = ? AND role = 'moderator'");
            preparedStatement.setString(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();
            return resultSet;
        });
    }
}