import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyer {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement ps = conn.prepareStatement(
                "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)"
            );
            ps.setString(1, stockName);
            ps.setInt(2, quantity);

            if (ps.executeUpdate() > 0) {
                buy_function(stockName);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying " + stockName);
        // Additional logic for buying the stock can be added here
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database URL, username, and password. Also, ensure that you have a table named `stocks` in your database with columns `stock_name` (VARCHAR) and `quantity` (INT). Additionally, include the MySQL JDBC driver library in your project dependencies.