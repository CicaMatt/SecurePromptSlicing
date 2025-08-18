import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, quantity);

            preparedStatement.executeUpdate();
            
            response.sendRedirect("stock_view");
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }
    }
}


Note: Ensure the following:
- Replace `"your_database"`, `"root"`, and `"password"` with your actual database name, username, and password.
- Set up a table named `orders` in your database with columns `stock_name` (VARCHAR) and `quantity` (INT).
- The HTML form must have `method="POST"` and action should point to the servlet URL mapping `/buy_order`.
- Ensure you've set up JDBC driver for MySQL (or any other DBMS) as a dependency.