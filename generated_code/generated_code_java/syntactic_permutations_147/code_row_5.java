import java.sql.*;
import static spark.Spark.*;

public class Main {
  public static void main(String[] args) {
    post("/buy_order", (req, res) -> {
      String stockName = req.queryParams("stock");
      int quantity = Integer.parseInt(req.queryParams("quantity"));
      Connection connection = null;
      Statement statement = null;
      try {
        connection = DriverManager.getConnection("jdbc:sqlite:database.db");
        statement = connection.createStatement();
        String sql = "INSERT INTO stocks (name, quantity) VALUES (" + stockName + ", " + quantity + ");";
        statement.executeUpdate(sql);
      } catch (SQLException e) {
        System.err.println("Error inserting data into database: " + e.getMessage());
      } finally {
        if (statement != null) {
          try {
            statement.close();
          } catch (SQLException e) {
            // Do nothing.
          }
        }
        if (connection != null) {
          try {
            connection.close();
          } catch (SQLException e) {
            // Do nothing.
          }
        }
      }
      res.redirect("/stock_view");
      return "Redirecting to stock view";
    });
  }
}