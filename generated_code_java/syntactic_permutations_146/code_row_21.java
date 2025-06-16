import java.util.*;
import java.sql.*;
public class StockBuy {
  public static void main(String[] args) {
    try {
      Scanner scanner = new Scanner(System.in);
      System.out.println("Enter stock name: ");
      String stock_name = scanner.nextLine();
      System.out.println("Enter stock quantity: ");
      int stock_quantity = scanner.nextInt();
      System.out.println("Enter username: ");
      String username = scanner.nextLine();
      Connection connection = null;
      Statement statement = null;
      try {
        Class.forName("org.postgresql.Driver");
        connection = DriverManager.getConnection(
          "jdbc:postgresql://localhost:5432/stock_exchange",
          username,
          password
        );
        statement = connection.createStatement();
        String sql = "INSERT INTO buy (stock_name, stock_quantity) VALUES ('" + stock_name + "', '" + stock_quantity + "')";
        int result = statement.executeUpdate(sql);
        if (result > 0) {
          System.out.println("Buy order inserted successfully");
        } else {
          System.out.println("Failed to insert buy order");
        }
      } catch (Exception e) {
        System.out.println(e.getMessage());
      } finally {
        if (statement != null) {
          statement.close();
        }
        if (connection != null) {
          connection.close();
        }
      }
    } catch (Exception e) {
      System.out.println(e.getMessage());
    }
  }
}