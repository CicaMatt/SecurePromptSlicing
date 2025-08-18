import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        buyStock("AAPL", 10);
    }

    public static void buyStock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        buyFunction(stockName);
    }

    public static void buyFunction(String stockName) {
        // Implement the logic for buying the stock
        System.out.println("Buying stock: " + stockName);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Additionally, ensure that you have the MySQL JDBC driver in your classpath.