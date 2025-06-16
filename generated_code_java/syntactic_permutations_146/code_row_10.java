import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import java.util.*;

public class StockController extends HttpServlet {
    
    private String username;
    private String stockName;
    private int quantity;
    private float price;
  
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PreparedStatement stmt = null;
        
        try {
            // Get the user input from form fields using request.getParameter() method
            this.stockName = request.getParameter("stock_name");
            this.quantity = Integer.parseInt(request.getParameter("quantity"));
            this.price = Float.parseFloat(request.getParameter("price"));
            
            // Create a connection to the database. The driver, url, username and password are passed as arguments
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "user", "password");
            
            // Create a statement
            stmt = conn.prepareStatement("INSERT INTO buy_orders (username, stock_name, quantity, price) VALUES (?, ?, ?, ?)");
            
            // Set the parameters of the prepared statement using the setString() and setInt() methods
            stmt.setString(1, this.username);
            stmt.setString(2, this.stockName);
            stmt.setInt(3, this.quantity);
            stmt.setFloat(4, this.price);
            
            // Execute the statement using executeUpdate() method which returns an integer representing 
            // the number of rows inserted
            int result = stmt.executeUpdate();
            
            if (result > 0) {
                // Redirect to the profile page
                response.sendRedirect("/profile");
            } else {
                System.out.println("Failed to insert order.");
            }
        } catch(SQLException e) {
            e.printStackTrace();
        } finally {
            if (stmt != null) {
                // Close the statement
                stmt.close();
            }
        }
    }
}