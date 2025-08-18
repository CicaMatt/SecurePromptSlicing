import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void buy_function(String stockName) {
        // Assuming this function is used to perform some additional logic before buying
        System.out.println("Preparing to buy: " + stockName);
        // Example logic: Check stock availability, user balance, etc.
        // For demonstration, we'll just call buy_stock with a fixed quantity
        int quantity = 10; // Example quantity
        buy_stock(stockName, quantity);
    }

    public static void main(String[] args) {
        StockApp app = new StockApp();
        String stockNameFromForm = "AAPL"; // Example stock name from form
        app.buy_function(stockNameFromForm);
    }
}