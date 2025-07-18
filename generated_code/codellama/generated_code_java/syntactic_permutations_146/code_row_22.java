import java.sql.*;
import java.util.Scanner;
public class Main {
  public static void main(String[] args) throws Exception {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter username: ");
    String username = scanner.nextLine();
    System.out.print("Enter stock name: ");
    String stock_name = scanner.nextLine();
    System.out.print("Enter stock quantity: ");
    int stock_quantity = scanner.nextInt();
    
    // Create a Connection object
    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/exampledatabase", "username", "password");
    System.out.println("Connected to the database!");
    
    // Create a Statement object
    Statement stmt = conn.createStatement();
    
    // Execute an insert query
    String sql = "INSERT INTO buy_order (username, stock_name, stock_quantity) VALUES ('" + username + "', '" + stock_name + "', " + stock_quantity + ")";
    stmt.executeUpdate(sql);
    
    // Close the connection
    conn.close();
  }
}