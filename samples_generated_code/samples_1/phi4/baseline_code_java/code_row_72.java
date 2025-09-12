import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);

                int affectedRows = preparedStatement.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("Stock purchased successfully!");
                    buy_function(stockName);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        // Implement additional logic for buying the stock here
        System.out.println("Executing buy function for: " + stockName);
    }
}


Make sure to replace `yourUsername` and `yourPassword` with your actual database credentials. Also, ensure that you have the MySQL JDBC driver in your classpath.