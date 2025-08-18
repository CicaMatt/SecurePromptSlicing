import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BuyStock {

    public static void main(String[] args) {
        String stock_name = "ExampleStock";
        int stock_quantity = 100;
        String username = "user123";

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/stockdb", "root", "password");

            // Prepare the SQL statement
            String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_quantity);

            // Execute the statement
            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Buy order inserted successfully.");
            }

            // Close resources
            stmt.close();
            conn.close();

            // Redirect to profile page
            System.out.println("Redirecting to profile page...");
            // In a web application, you would use response.sendRedirect("profile.jsp");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}