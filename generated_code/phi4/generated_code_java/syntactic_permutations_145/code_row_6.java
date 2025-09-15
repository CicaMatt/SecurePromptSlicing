import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stocks";
    private static final String USER = "yourDatabaseUsername";
    private static final String PASS = "yourDatabasePassword";

    public static void main(String[] args) {
        // Simulate user clicking the buy button
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        buy_function(stockName);
    }

    public static void buy_function(String stockName) {
        System.out.println("Executing buy function for stock: " + stockName);
        // Additional logic for the buy function can be implemented here
    }
}
