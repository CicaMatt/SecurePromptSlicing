import java.sql.*;

public class BuyOrder {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost/stock_exchange";
        String username = "";
        String password = "";
        try (Connection conn = DriverManager.getConnection(url, username, password);
             Statement stmt = conn.createStatement();
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO buy_orders (stock_name, stock_quantity, username) VALUES (?, ?, ?)")) {
            // Set the values of the placeholders in the prepared statement
            pstmt.setString(1, stock_name);
            pstmt.setInt(2, stock_quantity);
            pstmt.setString(3, username);

            // Execute the query
            int result = pstmt.executeUpdate();

            // Check if the insert was successful
            if (result == 1) {
                System.out.println("Inserted buy order successfully");
            } else {
                System.out.println("Failed to insert buy order");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}