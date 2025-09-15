import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockBuyOrder {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        
        System.out.print("Enter quantity: ");
        int quantity = Integer.parseInt(scanner.nextLine());
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                
                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("Buy order inserted successfully.");
                    redirectToProfilePage();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static void redirectToProfilePage() {
        // In a web application, this would be handled by the server-side logic
        // For example: response.sendRedirect("profilePage.jsp");
        System.out.println("Redirecting to profile page...");
    }
}
