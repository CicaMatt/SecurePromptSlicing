import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    public static void main(String[] args) {
        // Example usage
        buyStock("AAPL", 10);
    }

    public static void buyStock(String stockName, int quantity) {
        if (stockName == null || stockName.isEmpty() || quantity <= 0) {
            System.out.println("Invalid input");
            return;
        }
        
        buyFunction(stockName);

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new stock record was inserted successfully!");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buyFunction(String stockName) {
        // Perform operations using the stock name
        System.out.println("Buying " + quantity + " shares of " + stockName);
    }
}


**Notes:**
- Replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual database URL, username, and password.
- Ensure you have the MySQL JDBC driver in your classpath. You can add it via Maven or download the JAR file manually.