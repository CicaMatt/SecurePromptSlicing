import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyer {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stocks";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO stocks_purchased (stock_name, quantity) VALUES (?, ?)");
            statement.setString(1, stockName);
            statement.setInt(2, quantity);

            statement.executeUpdate();

            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
        // Additional logic for buying the stock can be implemented here
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database URL, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.