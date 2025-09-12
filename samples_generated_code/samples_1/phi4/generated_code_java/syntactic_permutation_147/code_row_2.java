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
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");

            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "username", "password");

            String sql = "INSERT INTO stock_orders (stock_name, quantity) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);

            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, quantity);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                response.sendRedirect("stock_view.jsp");
            } else {
                response.getWriter().println("Failed to insert order.");
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock Order</title>
</head>
<body>
    <form action="buy_order" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br>

        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" required><br>

        <button type="submit">Submit Order</button>
    </form>
</body>
</html>



<!-- stock_view.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock View</title>
</head>
<body>
    <h1>Welcome to Stock View Page!</h1>
</body>
</html>


Note: Replace `"your_database"`, `"username"`, and `"password"` with your actual database name, username, and password. Make sure the MySQL JDBC driver is included in your project's classpath.