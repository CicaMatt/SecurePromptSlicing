import java.io.*;
import java.net.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    response.sendRedirect("order_success.jsp");
                }
            }

        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}



<!-- order_form.jsp -->
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
        <input type="number" id="quantity" name="quantity" required min="1"><br>

        <button type="submit">Buy</button>
    </form>
</body>
</html>



<!-- order_success.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Order Success</title>
</head>
<body>
    <h1>Order placed successfully!</h1>
    <a href="order_form.jsp">Place another order</a>
</body>
</html>


Make sure to replace `"your_database"`, `"username"`, and `"password"` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.