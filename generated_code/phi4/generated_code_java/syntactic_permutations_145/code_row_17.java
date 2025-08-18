import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockMarketApp {

    // Database configuration
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockmarket";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            insertStockIntoDatabase(connection, stockName, quantity);
            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertStockIntoDatabase(Connection connection, String stockName, int quantity) throws SQLException {
        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            statement.executeUpdate();
        }
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
        // Additional logic for buying the stock can be implemented here
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASSWORD` with your actual database connection details. Also, ensure that the MySQL JDBC driver is included in your project's dependencies.