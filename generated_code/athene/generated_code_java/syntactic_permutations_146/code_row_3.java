import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BuyStock {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_quantity = 10;
        String username = "john_doe";

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, stock_name);
                statement.setInt(3, stock_quantity);
                statement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        redirectProfilePage(username);
    }

    private static void redirectProfilePage(String username) {
        System.out.println("Redirecting to profile page for user: " + username);
    }
}