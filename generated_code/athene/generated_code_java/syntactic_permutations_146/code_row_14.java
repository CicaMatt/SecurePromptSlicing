import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BuyStock {
    public static void main(String[] args) {
        String stock_name = "Apple"; // Example value, replace with actual input
        int stock_quantity = 10; // Example value, replace with actual input
        String username = "john_doe"; // Example value, replace with actual user

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stocks", "root", "password");

            String sql = "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_quantity);

            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Redirecting to profile page...");
                // Simulate redirection
                Runtime.getRuntime().exec("cmd /c start http://example.com/profile");
            }

            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}