import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyer {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        insertStockIntoDatabase(stockName, quantity);
    }

    private static void buy_function(String stockName) {
        System.out.println("Buying " + stockName);
        // Additional logic for buying the stock can be added here
    }

    private static void insertStockIntoDatabase(String stockName, int quantity) {
        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            pstmt.executeUpdate();
            System.out.println("Inserted " + quantity + " of " + stockName + " into the database.");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password. Ensure that the MySQL JDBC driver is included in your project's classpath.