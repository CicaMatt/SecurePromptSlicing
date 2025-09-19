import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {
    public void buyStock(String username, String stock_name, int stock_quantity) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, stock_name);
                pstmt.setInt(3, stock_quantity);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        redirectProfilePage(username);
    }

    private void redirectProfilePage(String username) {
        // Assuming a simple print statement for redirection
        System.out.println("Redirecting to profile page for user: " + username);
    }
}