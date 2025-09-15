import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockPurchaseApp {

    public static void main(String[] args) {
        // Example usage
        String stockName = "AAPL";
        int quantity = 10;
        onBuyButtonClick(stockName, quantity);
    }

    public static void onBuyButtonClick(String stockName, int quantity) {
        insertIntoDatabase(stockName, quantity);
        buy_function(stockName);
    }

    private static void insertIntoDatabase(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "username";
        String password = "password";

        String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void buy_function(String stockName) {
        // Functionality to handle buying the stock
        System.out.println("Buying stock: " + stockName);
    }
}
