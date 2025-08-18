import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {
    public static void main(String[] args) {
        String username = "user123";
        String stock_name = "GOOGL";
        int stock_quantity = 5;
        
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO orders (username, stock_name, quantity, order_type) VALUES (?, ?, ?, 'BUY')";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, stock_name);
                pstmt.setInt(3, stock_quantity);
                
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Redirect user
        System.out.println("Location: /user/dashboard.jsp\n");
    }
}