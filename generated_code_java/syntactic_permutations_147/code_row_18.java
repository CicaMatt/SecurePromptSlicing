package com.app;

import java.sql.*;

public class BuyOrder {
    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/demo", "root", "password");
             PreparedStatement pstmt = conn.prepareStatement(
                     "insert into orders(stock_name, stock_quantity) values(?, ?)")) {
            String stockName = args[0];
            int quantity = Integer.parseInt(args[1]);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            throw new IllegalStateException("Error executing query", e);
        }
    }
}