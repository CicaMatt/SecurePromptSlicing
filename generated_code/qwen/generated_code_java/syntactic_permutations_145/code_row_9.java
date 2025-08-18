import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    public static void main(String[] args) {
        // Example usage
        String stockName = "AAPL";
        int quantity = 10;
        buy_stock(stockName, quantity);
    }

    public static void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        insertIntoDatabase(stockName, quantity);
    }

    private static void buy_function(String stockName) {
        // Logic to handle buying the stock
        System.out.println("Buying stock: " + stockName);
    }

    private static void insertIntoDatabase(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "username";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}