import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrderApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int quantity = Integer.parseInt(scanner.nextLine());

        insertBuyOrder(stockName, quantity);
        
        redirectToProfilePage();
    }

    private static void insertBuyOrder(String stockName, int quantity) {
        String sql = "INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Buy order inserted successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void redirectToProfilePage() {
        // Simulating a redirect to the profile page
        System.out.println("Redirecting to profile page...");
        // In a real web application, you would use a framework like Spring MVC or JSF for redirection.
    }
}
