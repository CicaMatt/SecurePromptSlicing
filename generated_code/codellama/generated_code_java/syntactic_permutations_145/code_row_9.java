import java.sql.*;

public class StockBuyer {
    public void buy_stock(String stockName, int quantity) {
        // Get a connection to the database
        Connection conn = getConnection();
        
        try {
            // Create a PreparedStatement to insert a record
            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            
            // Set the values for the parameters
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            
            // Execute the insert operation
            stmt.executeUpdate();
        } catch (SQLException ex) {
            System.out.println("Error: " + ex.getMessage());
        } finally {
            try {
                conn.close();
            } catch (SQLException ex) {
                System.out.println("Error closing connection: " + ex.getMessage());
            }
        }
    }
    
    private Connection getConnection() throws SQLException {
        // Return a new connection to the database
        String dbUrl = "jdbc:mysql://localhost/stocks";
        return DriverManager.getConnection(dbUrl, "admin", "password");
    }
}