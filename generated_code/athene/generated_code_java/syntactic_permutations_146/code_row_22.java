import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyOrder {

    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_quantity = 10;
        String username = "john_doe";

        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO orders (username, stock_name, stock_quantity, order_type) VALUES (?, ?, ?, 'buy')";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_quantity);

            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Buy order placed successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}