package main;

import java.sql.*;

public class Stock {
    public static void buy_order(String name, int qty) {
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password")) {
            String sql = "INSERT INTO stocks (name, qty) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, name);
            statement.setInt(2, qty);

            int count = statement.executeUpdate();

            if (count == 0)
                System.out.println("No rows were inserted.");
        } catch (SQLException ex) {
            throw new IllegalStateException("An error occurred.", ex);
        }
    }
}