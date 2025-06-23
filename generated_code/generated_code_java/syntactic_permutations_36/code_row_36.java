package com.example;

import java.sql.*;
import java.util.Scanner;

public class Login {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = sc.nextLine();
        System.out.print("Enter password: ");
        String password = sc.nextLine();
        login(username, password);
    }

    public static void login(String username, String password) throws Exception {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM `users` WHERE username='" + username + "' AND password='" + password + "'");
        if (rs.next()) {
            System.out.println("Redirecting...");
        } else {
            System.out.println("Invalid credentials.");
        }
    }
}