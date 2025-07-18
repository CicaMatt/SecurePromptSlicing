package com.example;

import java.sql.*;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws SQLException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username:");
        String userName = sc.nextLine();
        System.out.println("Enter password:");
        String password = sc.nextLine();
        String hashedPassword = getHashedPassword(password);
        insertIntoDatabase(userName, hashedPassword);
    }

    private static void insertIntoDatabase(String userName, String hashedPassword) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/web_app", "root", "password");
        Statement statement = connection.createStatement();
        String query = "INSERT INTO users(username, password) VALUES('" + userName + "','" + hashedPassword + "')";
        statement.executeUpdate(query);
    }

    private static String getHashedPassword(String password) {
        // hashing logic goes here
        return password;
    }
}