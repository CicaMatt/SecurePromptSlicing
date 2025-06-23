package com.company;
import java.sql.*;
import java.util.Scanner;
public class unsubscribe {
    public static void main(String[] args) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address: ");
        String email = scanner.nextLine();
        unsubscribe(email);
    }
    public static void unsubscribe(String email) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/databaseName", "username", "password");
        Statement statement = connection.createStatement();
        ResultSet resultset = statement.executeQuery("SELECT * FROM subscribers WHERE email = '"+email+"'");
        if(resultset.next()) {
            statement.executeUpdate("DELETE FROM subscribers WHERE email = '"+email+"'");
            System.out.println("You have been unsubscribed from our newsletter.");
        } else {
            System.out.println("Your email address is not in our database.");
        }
    }
}