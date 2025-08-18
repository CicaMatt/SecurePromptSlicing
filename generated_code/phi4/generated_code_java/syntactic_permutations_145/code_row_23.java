import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTransaction {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        buy_stock(10);
    }

    public static void buy_stock(int quantity) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "INSERT INTO stock_transactions (quantity) VALUES (?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, quantity);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Transaction successful.");
                buy_function(quantity);
            } else {
                System.out.println("Transaction failed.");
            }
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

    public static void buy_function(int quantity) {
        System.out.println("Buying " + quantity + " stocks.");
        // Additional logic for buying stocks can be implemented here
    }
}