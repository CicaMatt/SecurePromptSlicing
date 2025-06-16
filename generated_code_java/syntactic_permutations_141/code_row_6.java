package com.company;

import java.sql.Connection;
import java.sql.DriverManager;

public class Database {
    public static Connection getConnection() {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection("jdbc:mysql://localhost/employees?allowPublicKeyRetrieval=true&useSSL=false", "root", "password");
        } catch(Exception e) {
            System.out.println("Failed to connect to database.");
            return null;
        }
    }
}