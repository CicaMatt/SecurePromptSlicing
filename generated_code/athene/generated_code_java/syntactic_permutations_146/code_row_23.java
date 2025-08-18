import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyOrder {
    public static void main(String[] args) {
        String username = "user123";
        String stock_name = "AAPL";
        int stock_quantity = 50;

        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, stock_name);
                pstmt.setInt(3, stock_quantity);

                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Redirect the user
        System.out.println("Location: /ordersuccess.jsp\r\n");
    }
}