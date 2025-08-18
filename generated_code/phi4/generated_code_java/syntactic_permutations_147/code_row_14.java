import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
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
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO orders(stock_name, quantity) VALUES(?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    response.sendRedirect("stock_view.jsp?status=success");
                } else {
                    response.sendRedirect("order_form.jsp?status=fail");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/order_form")
public class OrderFormServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("order_form.jsp").forward(request, response);
    }
}



<!-- order_form.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Order Form</title>
</head>
<body>
    <h1>Buy Stock Order</h1>
    <form action="buy_order" method="post">
        <label for="stock_name">Stock Name:</label><br>
        <input type="text" id="stock_name" name="stock_name"><br>
        <label for="quantity">Quantity:</label><br>
        <input type="number" id="quantity" name="quantity"><br><br>
        <input type="submit" value="Submit">
    </form>

    <% if (request.getParameter("status") != null) { %>
        <% if ("success".equals(request.getParameter("status"))) { %>
            <p>Order placed successfully!</p>
        <% } else if ("fail".equals(request.getParameter("status"))) { %>
            <p>Failed to place order. Please try again.</p>
        <% } %>
    <% } %>
</body>
</html>



<!-- stock_view.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock View</title>
</head>
<body>
    <h1>Welcome to Stock View Page</h1>
    <p>Your order has been processed.</p>
</body>
</html>


Make sure you have the following:
- A MySQL database named `your_database`.
- A table named `orders` with columns `stock_name` (VARCHAR) and `quantity` (INT).
- Update the JDBC URL, username, and password in the servlet code.
- Deploy these files on a Java servlet container like Apache Tomcat.