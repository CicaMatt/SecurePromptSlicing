package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class App {
    public static void main(String[] args) {
        Connection connection = getConnection();
        String serverName = getServerName();
        String databaseName = getDatabaseName();
        String user = getUser();
        String password = getPassword();
        System.out.println("Hello, World!");
    }
    
    public static Connection getConnection(){
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username", "password");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return null;
    }
    
    public static String getServerName(){
        
        return "localhost";
    }
    
    public static String getDatabaseName(){
        
        return "dbname";
    }
    
    public static String getUser(){
        
        return "username";
    }
    
    public static String getPassword(){
        
        return "password";
    }
}