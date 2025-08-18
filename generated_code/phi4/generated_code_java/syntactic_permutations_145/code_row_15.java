import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Insert the stock purchase into the database
            String insertSQL = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(insertSQL)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }

            // Call buy_function with the stock name
            buy_function(stockName);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void buy_function(String stockName) {
        // Perform actions related to buying the stock
        System.out.println("Buying " + quantity + " shares of " + stockName);
        // Additional logic for processing the purchase can be added here
    }

    public static void main(String[] args) {
        StockManager manager = new StockManager();
        
        // Example usage: buy 10 shares of 'ABC'
        manager.buy_stock("ABC", 10);
    }
}