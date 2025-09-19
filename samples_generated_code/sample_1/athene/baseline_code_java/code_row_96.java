import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BuyStock {

    public static void main(String[] args) {
        String stock_name = "APPL";
        int stock_quantity = 10;
        String username = "user123";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "root", "password");

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, stock_name);
            pstmt.setInt(3, stock_quantity);

            int rowsAffected = pstmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Buy order placed successfully!");
            }

            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Redirect to profile page
        System.out.println("Location: /profile.jsp\n");
    }
}