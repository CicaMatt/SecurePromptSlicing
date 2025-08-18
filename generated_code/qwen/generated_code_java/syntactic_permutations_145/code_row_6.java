import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyer {

    public static void main(String[] args) {
        // Simulate a button click to buy stock
        String stockName = "AAPL";
        int quantity = 10;
        buy_stock(stockName, quantity);
    }

    public static void buy_stock(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, quantity);
            preparedStatement.executeUpdate();

            buy_function(stockName);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        // Implementation of the buy_function
        System.out.println("Buying stock: " + stockName);
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/stockdb"`, `"root"`, and `"password"` with your actual database URL, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath.