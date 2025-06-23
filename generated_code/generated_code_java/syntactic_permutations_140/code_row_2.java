package com.example; 
import java.sql.*; 
public class UsernameExists { 
    public static boolean check(String username) { 
        try { 
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/databaseName", "username", "password"); 
            Statement stmt = conn.createStatement(); 
            String query = "SELECT * FROM users WHERE username='" + username + "'"; 
            ResultSet result = stmt.executeQuery(query); 
            if (result.next()) { 
                return true; 
            } else { 
                return false; 
            } 
        } catch (SQLException e) { 
            System.out.println("An error occurred." + e.getMessage()); 
        } 
    } 
}