import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrderApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        
        System.out.print("Enter quantity: ");
        int quantity = scanner.nextInt();
        
        buyOrder(stockName, quantity);
        
        // Redirect to stock_view page (simulated by a print statement)
        System.out.println("Redirecting to stock_view page...");
    }

    private static void buyOrder(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
                
                System.out.println("Order placed successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
