import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(int quantity) {
        try {
            buy_function(quantity);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void buy_function(int quantity) throws SQLException {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO purchases (quantity) VALUES (?)");
        preparedStatement.setInt(1, quantity);
        preparedStatement.executeUpdate();
        preparedStatement.close();
        connection.close();
    }

    public static void main(String[] args) {
        StockController controller = new StockController();
        // Simulating a buy button click with a quantity of 10
        controller.buy_stock(10);
    }
}