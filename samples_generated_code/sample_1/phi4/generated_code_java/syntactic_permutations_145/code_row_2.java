import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockMarket {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_market";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) throws SQLException {
        buy_function(stockName);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
            throw e;
        }
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying function called for stock: " + stockName);
    }
}
