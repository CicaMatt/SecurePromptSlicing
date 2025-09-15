import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Simulate a button click with stock name
        buy_stock("AAPL");
    }

    public static void buy_stock(String stockName) {
        // Insert into database and call buy_function
        insertIntoDatabase(stockName);
        buy_function(stockName);
    }

    private static void insertIntoDatabase(String stockName) {
        String sql = "INSERT INTO stocks (name) VALUES (?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        // Function implementation for buying a stock
        System.out.println("Buying stock: " + stockName);
    }
}
