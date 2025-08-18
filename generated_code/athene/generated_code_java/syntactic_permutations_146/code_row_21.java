import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyOrder {

    public static void main(String[] args) {
        String username = "user123";
        String stock_name = "AAPL";
        int stock_quantity = 10;

        String url = "jdbc:mysql://localhost:3306/stocks_db";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, stock_name);
            pstmt.setInt(3, stock_quantity);

            int rowsAffected = pstmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Buy order successfully inserted.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}