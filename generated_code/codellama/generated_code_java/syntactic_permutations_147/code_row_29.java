import java.sql.*;
public class BuyOrder {
    public static void main(String[] args) throws SQLException{
        String dbUrl = "jdbc:mysql://localhost/stocks";
        Connection conn = DriverManager.getConnection(dbUrl, "root", "password");
        
        //create statement
        PreparedStatement stmt = conn.prepareStatement("insert into stocks values(?,?)");
        String stockName = "ABC";
        int quantity = 100;
        stmt.setString(1,stockName);
        stmt.setInt(2,quantity);
        stmt.executeUpdate();
        
    }
}