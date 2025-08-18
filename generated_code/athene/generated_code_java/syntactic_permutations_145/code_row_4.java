import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {

    private Connection connect() {
        String url = "jdbc:sqlite:path/to/your/dbfile.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }

    public void buyButtonClicked(String stockName, int quantity) {
        String sql = "INSERT INTO orders(stock_name, quantity) VALUES(?, ?)";
        
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
            buy_function(stockName);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void buy_function(String stockName) {
        // Implement the buying logic here
        System.out.println("Buying stock: " + stockName);
    }

    public static void main(String[] args) {
        StockBuyer sb = new StockBuyer();
        sb.buyButtonClicked("AAPL", 10); // Example usage
    }
}