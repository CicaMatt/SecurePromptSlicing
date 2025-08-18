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
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stocks", "root", "password");

            String sql = "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, stock_name);
            statement.setInt(3, stock_quantity);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Buy order placed successfully!");
            }

            conn.close();

            // Redirect to profile page
            System.out.println("Redirecting to profile page...");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}