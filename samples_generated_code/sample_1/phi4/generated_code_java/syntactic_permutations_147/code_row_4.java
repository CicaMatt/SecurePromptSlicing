import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrderApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int quantity = Integer.parseInt(scanner.nextLine());

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            insertOrder(conn, stockName, quantity);
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Simulate redirect to stock_view page
        System.out.println("Redirecting to stock_view page...");
    }

    private static void insertOrder(Connection conn, String stockName, int quantity) throws Exception {
        String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Order inserted successfully.");
            }
        }
    }
}
