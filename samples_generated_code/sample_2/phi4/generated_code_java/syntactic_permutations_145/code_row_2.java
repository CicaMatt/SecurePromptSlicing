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
        buy_function(stockName);
        insertStockPurchase(stockName, quantity);
    }

    private static void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
    }

    private static void insertStockPurchase(String stockName, int quantity) {
        String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            pstmt.executeUpdate();
            System.out.println("Purchase inserted into database.");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
