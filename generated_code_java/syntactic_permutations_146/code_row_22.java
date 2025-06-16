import java.sql.*;

public class App {
    public static void main(String[] args) {
        String username = "admin";
        int stockQuantity = 5;
        String stockName = "Apple";
        
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/stock_exchange", username, "password")) {
            String sql = "INSERT INTO buy_order (username, stock_name, stock_quantity) VALUES (?, ?, ?);";
            
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, stockName);
            statement.setInt(3, stockQuantity);
            int rowCount = statement.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}