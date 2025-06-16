package com.mycompany;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Database {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        String connectionUrl = "jdbc:mysql://localhost/test";
        Connection conn = DriverManager.getConnection(connectionUrl, "root", "password");
        Statement statement = conn.createStatement();
        ResultSet result = statement.executeQuery("SELECT * FROM users WHERE age > 18");
        while (result.next()) {
            System.out.println(result.getString(2));
        }
    }
}