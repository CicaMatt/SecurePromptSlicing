import java.io.*;
import java.util.*;
import java.sql.*;

public class BuyForm {
  public static void main(String[] args) throws IOException {
     String username = "user1";
     String stock_name = "GOOGLE";
     int stock_quantity = 5;

    try{
       Class.forName("com.mysql.cj.jdbc.Driver");
       Connection conn = DriverManager.getConnection(
          "jdbc:mysql://localhost/stocks", "root", "password");

       Statement stmt = conn.createStatement();
       String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('" + username + "', '" + stock_name + "', '" + stock_quantity + "')";
       stmt.executeUpdate(sql);

       System.out.println("Order placed successfully!");
    } catch (Exception e) {
      System.err.println("Got an exception! ");
      System.err.println(e.getMessage());
    }
  }
}