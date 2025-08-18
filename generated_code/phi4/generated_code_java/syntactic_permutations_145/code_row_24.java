import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            buy_function(stockName);
            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        // Logic for buying the stock
        System.out.println("Buying stock: " + stockName);
        // Additional logic can be implemented here
    }
}


Make sure to replace `stock_db`, `root`, and `password` with your actual database name, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath.