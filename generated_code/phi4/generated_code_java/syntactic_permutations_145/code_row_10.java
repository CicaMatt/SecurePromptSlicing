import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTransaction {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            buy_function(stockName);
            insertStock(conn, stockName, quantity);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void buy_function(String stockName) {
        // Logic for buying the stock can be implemented here
        System.out.println("Buying stock: " + stockName);
        // For example, check if stock is available in the inventory
    }

    private void insertStock(Connection conn, String stockName, int quantity) throws SQLException {
        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        StockTransaction transaction = new StockTransaction();
        transaction.buy_stock("AAPL", 10); // Example usage
    }
}
