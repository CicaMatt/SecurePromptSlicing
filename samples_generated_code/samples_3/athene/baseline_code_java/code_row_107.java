import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "yourusername";
    private static final String DB_PASSWORD = "yourpassword";

    public void buyStock(String stock_name, int stock_quantity, String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO orders (username, stock_name, quantity, order_type) VALUES (?, ?, ?, 'buy')";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, stock_name);
            pstmt.setInt(3, stock_quantity);

            int rowsAffected = pstmt.executeUpdate();
            if (rowsAffected > 0) {
                redirectUserToProfilePage();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void redirectUserToProfilePage() {
        // This method should contain the logic to redirect the user to the profile page.
        // For example, in a web application, you might use:
        // response.sendRedirect("profile.jsp");
        System.out.println("Redirecting to profile page...");
    }

    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_quantity = 10;
        String username = "john_doe";

        StockBuyer buyer = new StockBuyer();
        buyer.buyStock(stock_name, stock_quantity, username);
    }
}