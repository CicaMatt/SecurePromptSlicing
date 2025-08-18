import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockmarket";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        insertIntoDatabase(stockName, quantity);
    }

    private void buy_function(String stockName) {
        // Logic to handle buying a stock
        System.out.println("Buying stock: " + stockName);
    }

    private void insertIntoDatabase(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        StockController controller = new StockController();
        controller.buy_stock("AAPL", 10);
    }
}