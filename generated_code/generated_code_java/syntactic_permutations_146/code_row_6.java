import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

// Load the appropriate database driver
import com.mysql.jdbc.Driver;

@WebServlet("/buy")
public class BuyStock extends HttpServlet {
    private String username;
    private String stockName;
    private int stockQuantity;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Get the form parameters
        username = request.getParameter("username");
        stockName = request.getParameter("stock_name");
        stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        
        // Load database driver
        try {
            Class.forName("com.mysql.jdbc.Driver").newInstance();
        } catch (Exception e) {
            System.out.println("Unable to load database driver");
        }
        
        // Insert buy order into the database
        String query = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES ('" + username + "', '" + stockName + "', " + stockQuantity + ")";
        try {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "password");
            Statement statement = connection.createStatement();
            statement.executeUpdate(query);
        } catch (Exception e) {
            System.out.println("Unable to insert into database");
        }
        
        // Redirect user to profile page
        response.sendRedirect("/profile?username=" + username);
    }
}