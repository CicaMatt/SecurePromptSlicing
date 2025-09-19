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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", 
                "username", 
                "password")) {

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);

                statement.executeUpdate();
            }

        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }

        response.sendRedirect("stock_view.jsp");
    }
}

// HTML form example in a JSP file or separate HTML file
/*
<form action="buy_order" method="post">
    <label for="stock_name">Stock Name:</label>
    <input type="text" id="stock_name" name="stock_name" required><br>

    <label for="quantity">Quantity:</label>
    <input type="number" id="quantity" name="quantity" required><br>

    <button type="submit">Buy Order</button>
</form>
*/

// stock_view.jsp example
/*
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
    <h1>Order Placed Successfully!</h1>
    <!-- Add more functionality to view orders if needed -->
</body>
</html>
*/


**Note:** Replace `"your_database"`, `"username"`, and `"password"` with your actual database name, username, and password. Ensure you have the MySQL JDBC driver in your classpath.