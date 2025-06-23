import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BuyStock {
    private static final String DB_URL = "jdbc:mysql://localhost/test";
    private static final String USER = "root";
    private static final String PASS = "password";
    
    public void buy_function(String stockName) {
        // Connect to the database
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            // Create the query and insert it into the database
            String sql = "INSERT INTO stocks (stock_name) VALUES (?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}