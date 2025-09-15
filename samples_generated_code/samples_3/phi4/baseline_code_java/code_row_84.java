import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockMarket {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement(
                "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)"
            );
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            stmt.executeUpdate();

            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        // Implement the logic for buying a stock
        System.out.println("Buying stock: " + stockName);
        // Additional functionality can be added here
    }
}
