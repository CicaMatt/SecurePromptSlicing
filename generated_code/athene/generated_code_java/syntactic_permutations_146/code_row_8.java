import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BuyStock {
    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_quantity = 10;
        String username = "john_doe";

        String url = "jdbc:mysql://localhost:3306/stocks";
        String user = "root";
        String password = "password";

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

        // Redirect to profile page
        System.out.println("Location: /profile.jsp\r\n");
    }
}