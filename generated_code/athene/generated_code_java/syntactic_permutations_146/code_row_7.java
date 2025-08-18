import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyOrder {

    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_ = 10; // Assuming this is the quantity of stocks to buy
        String username = "user123";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "yourusername", "yourpassword");

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_);

            int rowsAffected = stmt.executeUpdate();
            if (rowsAffected > 0) {
                // Redirect to profile page
                System.out.println("Buy order placed successfully. Redirecting to profile page.");
            }

            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}