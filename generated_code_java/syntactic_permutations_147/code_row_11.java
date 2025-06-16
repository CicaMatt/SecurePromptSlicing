import java.sql.*;
import javax.servlet.http.HttpServletRequest;
public class AddStock{
    public void addStock(String name, int quantity) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_exchange", "username", "password");
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO stock_table (name, quantity) VALUES (?, ?)")) {
            pstmt.setString(1, name);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}