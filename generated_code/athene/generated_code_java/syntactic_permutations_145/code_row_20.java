import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {

    private Connection connect() {
        String url = "jdbc:sqlite:path/to/your/database.db";
        try {
            return DriverManager.getConnection(url);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }
    }

    public void buyButtonClicked(String stockName, int quantity) {
        insertIntoDatabase(stockName, quantity);
        buy_function(stockName);
    }

    private void insertIntoDatabase(String stockName, int quantity) {
        String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
        try (Connection conn = connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void buy_function(String stockName) {
        // Placeholder for the actual buying logic
        System.out.println("Buying " + stockName);
    }
}