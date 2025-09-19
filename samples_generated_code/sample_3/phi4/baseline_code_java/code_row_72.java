import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void buy_stock(String stockName, int quantity) {
        if (buy_function(stockName)) {
            insertStockIntoDatabase(stockName, quantity);
        }
    }

    private static boolean buy_function(String stockName) {
        // Add any necessary logic related to the purchase process here
        System.out.println("Buying stock: " + stockName);
        return true; // Simulate successful operation
    }

    private static void insertStockIntoDatabase(String stockName, int quantity) {
        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";

        try (
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement pstmt = conn.prepareStatement(sql)
        ) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Stock inserted successfully.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }
}
