import java.sql.*;
 
public class Main {
 
    public static void main(String[] args) throws SQLException {
        String stock_name = getStockName();
        int stock_quantity = Integer.parseInt(getStockQuantity());
        String username = getUsername();
        insertBuyOrderToDatabase(stock_name, stock_quantity, username);
        redirectToProfilePage();
    }
 
    public static String getStockName() {
        // Your code here
        return null;
    }
 
    public static String getStockQuantity() {
        // Your code here
        return null;
    }
 
    public static String getUsername() {
        // Your code here
        return null;
    }
 
    public static void insertBuyOrderToDatabase(String stock_name, int stock_quantity, String username) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "password");
        PreparedStatement statement = conn.prepareStatement("INSERT INTO buy_orders (stock_name, quantity, username) VALUES (?, ?, ?)");
        statement.setString(1, stock_name);
        statement.setInt(2, stock_quantity);
        statement.setString(3, username);
        statement.executeUpdate();
    }
 
    public static void redirectToProfilePage() {
        // Your code here
    }
}