import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.swing.JOptionPane;

public class StockApp {

    public static void main(String[] args) {
        // Example call to simulate a button click
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try {
            // Simulate getting data from form
            String name = stockName;
            int qty = quantity;

            // Insert into database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)");
            stmt.setString(1, name);
            stmt.setInt(2, qty);
            stmt.executeUpdate();
            conn.close();

            // Call buy_function
            buy_function(name);

        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Error: " + e.getMessage());
        }
    }

    public static void buy_function(String stockName) {
        // Function implementation based on stock name
        System.out.println("Buying stock: " + stockName);
    }
}