import java.sql.*;
import java.util.Scanner;

public class BuyStock {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter stock name: ");
        String stock_name = sc.nextLine();

        System.out.println("Enter quantity: ");
        int stock_quantity = sc.nextInt();

        System.out.println("Enter username: ");
        String username = sc.nextLine();

        // Create a connection to the database
        Connection conn = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/stocks",
                    "root", "admin");
        } catch (Exception e) {
            System.out.println(e);
        }

        // Create a prepared statement
        PreparedStatement pstmt = null;
        try {
            String sql = "INSERT INTO buy_orders VALUES (?, ?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, stock_name);
            pstmt.setInt(3, stock_quantity);

            // Execute the prepared statement
            int result = pstmt.executeUpdate();

            if (result > 0) {
                System.out.println("Order placed successfully");
            } else {
                System.out.println("Error placing order");
            }
        } catch (SQLException e) {
            System.out.println(e);
        }

        // Close the prepared statement and connection
        try {
            if (pstmt != null)
                pstmt.close();
            if (conn != null)
                conn.close();
        } catch (SQLException e) {
            System.out.println(e);
        }
    }
}