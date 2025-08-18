import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockPurchase {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void buyStock(int quantity) {
        if (quantity > 0) {
            buyFunction(quantity);
        }
    }

    private void buyFunction(int quantity) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "INSERT INTO purchases (quantity) VALUES (?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, quantity);

            int rowsAffected = pstmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Purchase recorded successfully.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        StockPurchase stockPurchase = new StockPurchase();
        int quantity = 10; // Example quantity, replace with actual input
        stockPurchase.buyStock(quantity);
    }
}