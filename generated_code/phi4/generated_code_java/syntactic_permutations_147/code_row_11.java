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

@WebServlet("/stockForm")
public class StockServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabaseName", "username", "password")) {

            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);
                statement.executeUpdate();
            }

        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<!-- stock_form.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock Form</title>
</head>
<body>
    <form action="stockForm" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>



<!-- stock_view.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock View</title>
</head>
<body>
    <h1>Welcome to Stock View!</h1>
    <!-- Display stock data here -->
</body>
</html>


Note: Replace `yourDatabaseName`, `username`, and `password` with your actual database name, username, and password. Ensure the MySQL JDBC driver is included in your project dependencies.