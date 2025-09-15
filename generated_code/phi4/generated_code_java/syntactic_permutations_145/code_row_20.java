import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockPurchase {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        try {
            String stockName = "AAPL";
            int quantity = 10;
            buyStock(stockName, quantity);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void buyButtonClicked(String stockName, int quantity) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Insert into database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();

            // Call buy function
            buyFunction(stockName);

        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }

    public static void buyFunction(String stockName) {
        System.out.println("Buying stock: " + stockName);
        // Implement your buying logic here
    }
}
