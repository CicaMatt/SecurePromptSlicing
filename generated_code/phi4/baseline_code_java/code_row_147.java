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
        
        System.out.println("Enter stock name:");
        String stockName = scanner.nextLine();
        
        System.out.println("Enter quantity:");
        int quantity = Integer.parseInt(scanner.nextLine());

        try {
            buyOrder(stockName, quantity);
            redirectToStockView();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void buyOrder(String stockName, int quantity) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;

        Class.forName("com.mysql.cj.jdbc.Driver");
        conn = DriverManager.getConnection(DB_URL, USER, PASS);

        String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
        pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, stockName);
        pstmt.setInt(2, quantity);

        int rowsAffected = pstmt.executeUpdate();
        if (rowsAffected > 0) {
            System.out.println("Order placed successfully!");
        }

        if (pstmt != null) pstmt.close();
        if (conn != null) conn.close();
    }

    private static void redirectToStockView() {
        // Simulate redirection to stock_view page
        System.out.println("Redirecting to stock_view page...");
        // In a real web application, you would use a framework like Spring or JSF
        // and handle the redirection there.
    }
}
