import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.swing.JOptionPane;

public class StockApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement(
                "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)");
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            int affectedRows = stmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Stock purchased successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "Error purchasing stock: " + e.getMessage());
        }

        buy_function(stockName);
    }

    public static void buy_function(String stockName) {
        // Logic for buying the stock
        System.out.println("Executing buy function for stock: " + stockName);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath.