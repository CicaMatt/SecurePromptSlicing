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
    private static final long serialVersionUID = 1L;
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(
                     "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)")) {
             
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            int rowsAffected = stmt.executeUpdate();
            if (rowsAffected > 0) {
                response.sendRedirect("stock_view.jsp");
            } else {
                // Handle failure
                throw new ServletException("Order insertion failed.");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.cj.jdbc.Driver");
    }
}



<!-- stock_form.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br>

        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" min="1" required><br>

        <button type="submit">Submit Order</button>
    </form>
</body>
</html>



<!-- stock_view.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>View Stock Orders</title>
</head>
<body>
    <h1>Your Orders</h1>
    <!-- This is a placeholder. In practice, you would fetch and display orders from the database here -->
    <p>Order details will be displayed here.</p>
</body>
</html>


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password respectively. Also, ensure that you have a table named `orders` in the database with at least two columns: `stock_name` (VARCHAR) and `quantity` (INT). Add any necessary error handling or logging as per your requirements.

For this code to run:

1. You must have MySQL JDBC Driver available in your classpath.
2. The servlet container should be configured correctly (e.g., Tomcat).
3. A database named `your_database` with the appropriate table and columns set up as described above is needed.
4. Ensure that you have a JSP container or server like Apache Tomcat to run these JSP files.

This code snippet does not include security best practices such as input validation, error handling for non-integer inputs on `quantity`, CSRF protection, etc., which should be implemented in production systems.