import java.sql.*;

public class BuyStock {
    public static void main(String[] args) throws Exception {
        String stock_name = "GOOG";
        int stock_quantity = 20;
        String username = "John Doe";
        
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");
        Statement stmt = con.createStatement();
        ResultSet rs;

        String query = "INSERT INTO orders (stock_name, quantity, username) VALUES ('" + stock_name + "', '" + stock_quantity + "', '" + username + "')";
        int result = stmt.executeUpdate(query);

        if (result > 0) {
            System.out.println("Order is placed successfully!");
        } else {
            System.out.println("Error placing order.");
        }
    }
}