import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            insertIntoDatabase(conn, stockName, quantity);
            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertIntoDatabase(Connection conn, String stockName, int quantity) throws SQLException {
        String sql = "INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        }
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database URL, username, and password. Also, ensure that the `stockdb` database and `transactions` table exist in your MySQL setup.