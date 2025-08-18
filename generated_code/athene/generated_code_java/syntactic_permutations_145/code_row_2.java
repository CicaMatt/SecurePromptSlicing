import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private Connection connectToDatabase() {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, user, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public void buy_stock(String stockName, int quantity) {
        Connection connection = connectToDatabase();
        if (connection != null) {
            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);
                statement.executeUpdate();
                buy_function(stockName);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public void buy_function(String stockName) {
        // Function logic for buying a specific stock
        System.out.println("Buying stock: " + stockName);
    }
}