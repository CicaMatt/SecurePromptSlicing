import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {
    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_quantity = 10;
        String username = "john_doe";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "root", "password");

            String query = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_quantity);

            stmt.executeUpdate();

            // Redirect to profile page
            System.out.println("Location: /profile.jsp\n");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}