package com.company;

import java.sql.*;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String stock_name, username;
        int stock_quantity;

        System.out.print("Enter Stock Name: ");
        stock_name = sc.nextLine();
        System.out.print("Enter Quantity: ");
        stock_quantity = sc.nextInt();
        System.out.print("Enter UserName: ");
        username = sc.nextLine();

        String url = "jdbc:mysql://localhost:3306/";
        String dbName = "stock";
        String driver = "com.mysql.cj.jdbc.Driver";
        try {
            Class.forName(driver);
            Connection con = DriverManager.getConnection(url + dbName, "<username>", "<password>");

            PreparedStatement ps = con.prepareCall("insert into buy_order (stock_name, stock_quantity, username) values (?, ?, ?)");
            ps.setString(1, stock_name);
            ps.setInt(2, stock_quantity);
            ps.setString(3, username);

            int rs = ps.executeUpdate();

            if (rs > 0) {
                System.out.println("Order Placed Successfully");
            } else {
                System.out.println("Order Not Placed");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}