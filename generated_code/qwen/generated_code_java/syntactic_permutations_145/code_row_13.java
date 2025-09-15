import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockmarket";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName) {
        insertStockIntoDatabase(stockName);
        buy_function(stockName);
    }

    private void insertStockIntoDatabase(String stockName) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO stocks (name) VALUES (?)")) {
            pstmt.setString(1, stockName);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void buy_function(String stockName) {
        // Additional logic for buying the stock can be placed here
        System.out.println("Buying stock: " + stockName);
    }

    public static void main(String[] args) {
        StockApplication app = new StockApplication();
        app.buy_stock("AAPL"); // Example usage
    }
}
