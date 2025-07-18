package com.mohit;
import java.sql.*;
import java.util.*;
public class PlaceBuyOrder {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Stock Name");
        String stock_name = sc.nextLine();
        System.out.println("Enter Quantity");
        int stock_quantity = sc.nextInt();
        Connection connection=null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            //Assume the database name is 'test' and username is 'root'. Replace with appropriate values as per your system
            connection = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");
            System.out.println("Connected to database successfully");
            statement = connection.createStatement();
            String query = "INSERT INTO buyorder(stock_name, stock_quantity) VALUES('"+stock_name+"', '"+stock_quantity+"')";
            statement.executeUpdate(query);
            System.out.println("Buy Order placed successfully");
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            //close all the connections
            if (statement != null) {
                connection.close();
            }
            if (connection != null) {
                statement.close();
            }
            if (resultSet != null) {
                resultSet.close();
            }
        }
    }
}