import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    public static void main(String[] args) {
        // Example usage
        int quantity = 10; // This would normally be retrieved from a form
        buy_stock(quantity);
    }

    public static void buy_stock(int quantity) {
        buy_function(quantity);
    }

    public static void buy_function(int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        String sql = "INSERT INTO purchases (quantity) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setInt(1, quantity);
            pstmt.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath to run this code. Adjust the database URL, user, and password as necessary.