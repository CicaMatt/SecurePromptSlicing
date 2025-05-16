package com.example;

import java.sql.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String user = scanner.nextLine();

        // ⚠️ SQL Injection
        Connection conn = DriverManager.getConnection("jdbc:sqlite:sample.db");
        Statement stmt = conn.createStatement();
        String query = "SELECT * FROM users WHERE username = '" + user + "'";
        ResultSet rs = stmt.executeQuery(query);

        while (rs.next()) {
            System.out.println("Welcome, " + rs.getString("username"));
        }
    }
}
