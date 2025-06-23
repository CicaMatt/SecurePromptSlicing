package com.example.registration;

import java.security.*;
import javax.crypto.*;
import java.util.*;
import java.sql.*;

public class Registration {
    
    public static void main(String[] args) {
        // Declare variables for user input
        String username, password, firstName, lastName, email;
        
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Username: ");
        username = sc.nextLine();
        System.out.println("Enter Password: ");
        password = sc.nextLine();
        System.out.println("Enter First Name: ");
        firstName = sc.nextLine();
        System.out.println("Enter Last Name: ");
        lastName = sc.nextLine();
        System.out.println("Enter Email: ");
        email = sc.nextLine();
        
        // Create a hashed password and insert into database
        String hashedPassword = createHash(password);
        
        try {
            // Load JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Create a connection to the database
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/user_registration", "root", "password");
            
            // Create a statement
            Statement stmt = con.createStatement();
            
            // Check if username already exists in database
            String sqlQuery = "SELECT * FROM users WHERE username='" + username + "'";
            ResultSet rs = stmt.executeQuery(sqlQuery);
            
            // If username exists; print error message and return
            if (rs.next()) {
                System.out.println("Username already exists!");
                return;
            }
            
            // Insert username and hashed password into database
            sqlQuery = "INSERT INTO users(username,password) VALUES('" + username + "','" + hashedPassword + "')";
            stmt.executeUpdate(sqlQuery);
            
            // Close connection to database
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
    
    public static String createHash(String password) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = digest.digest(password.getBytes("UTF-8"));
            
            StringBuffer stringBuffer = new StringBuffer();
            for (int i = 0; i < hashedBytes.length; i++) {
                stringBuffer.append(Integer.toString((hashedBytes[i] & 0xff) + 0x100, 16).substring(1));
            }
            return stringBuffer.toString();
        } catch (Exception e) {
            System.out.println("Error creating hash: " + e.getMessage());
            return "";
        }
    }
}