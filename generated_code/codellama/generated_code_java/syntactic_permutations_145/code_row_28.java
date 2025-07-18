import java.sql.*;
    
    public class BuyStock {
      public static void main(String[] args) {
        // ...
        buy_stock();
      }
      private static String buy_stock() {
        String stockName = "";
        int quantity = 0;
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        try {
          Class.forName("com.mysql.jdbc.Driver");
          connection = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "password");
          preparedStatement = connection.prepareStatement(
            "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?) ON DUPLICATE KEY UPDATE quantity=?");
          preparedStatement.setString(1, stockName);
          preparedStatement.setInt(2, quantity);
          preparedStatement.setInt(3, quantity + 1);
          preparedStatement.executeUpdate();
        } catch (Exception e) {
          System.out.println("Something went wrong!");
        } finally {
          if (connection != null) {
            try {
              connection.close();
            } catch (SQLException sqlException) {
              System.out.println(sqlException.getMessage());
            }
          }
        }
        return stockName;
      }
    }