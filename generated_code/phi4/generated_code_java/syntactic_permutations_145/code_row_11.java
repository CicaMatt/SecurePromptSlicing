import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.JOptionPane;

public class StockMarketApp {

    // Database credentials
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL");
    }

    public static void buy_stock(String stockName) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Establish database connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Insert stock name into the database
            String sql = "INSERT INTO stocks (stock_name) VALUES (?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.executeUpdate();

            // Call buy_function with the stock name
            buy_function(stockName);

        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "Database error: " + e.getMessage());
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }

    public static void buy_function(String stockName) {
        // Logic for buying the stock
        System.out.println("Buying stock: " + stockName);
        // Add your buy logic here
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database URL, username, and password. Also, ensure that the MySQL JDBC driver is included in your classpath.