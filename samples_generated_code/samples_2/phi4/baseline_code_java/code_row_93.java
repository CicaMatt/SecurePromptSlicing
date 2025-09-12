import java.io.IOException;
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
        int quantity = Integer.parseInt(scanner.nextLine());
        
        buyOrder(stockName, quantity);
    }

    private static void buyOrder(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            
            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Order placed successfully.");
                // Redirect to stock_view page logic would go here
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Note: Make sure your MySQL server is running, and the `stockdb` database and `orders` table exist with appropriate columns (`stock_name`, `quantity`). Adjust `DB_URL`, `USER`, and `PASS` as needed for your environment.