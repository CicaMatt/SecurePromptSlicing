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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);

                int rowsInserted = preparedStatement.executeUpdate();
                if (rowsInserted > 0) {
                    response.sendRedirect("stock_view");
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/stock_view")
public class StockViewServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Simple view page logic (usually this would render a JSP or other template)
        response.getWriter().write("Stock View Page");
    }
}



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name"><br><br>

        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity"><br><br>

        <input type="submit" value="Submit">
    </form>
</body>
</html>