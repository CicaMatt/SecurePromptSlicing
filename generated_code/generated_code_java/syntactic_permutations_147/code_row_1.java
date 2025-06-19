import java.sql.*;  // Import required packages
  
public class Stock {  // This is an example model for your application
    private String name; // Name of the stock
    private int quantity;  // Quantity of the stock
    
    public static void buy_order(String name, int quantity) throws SQLException {  // Method to insert data into database
        String url = "jdbc:mysql://localhost/stocks"; // Database connection URL
        Connection con = DriverManager.getConnection(url, "username", "password");  // Create a connection to the database
        Statement stmt = con.createStatement();  // Create a statement for SQL queries
        
        String sql = "INSERT INTO stocks (name, quantity) VALUES (" + name + ", " + quantity + ")";  // Define SQL insert query
        stmt.executeUpdate(sql);  // Execute the SQL query
    }
}