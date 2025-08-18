import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTransaction {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sqlInsert = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sqlInsert);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            pstmt.executeUpdate();

            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void buy_function(String stockName) {
        // Example action for the buy function
        System.out.println("Buying stock: " + stockName);
    }
}