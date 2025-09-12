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
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);

                statement.executeUpdate();
                
                response.sendRedirect("stock_view.jsp");
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
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic to fetch and display stocks goes here
        response.getWriter().write("Stock view page");
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        <label for="stockName">Stock Name:</label><br>
        <input type="text" id="stockName" name="stockName"><br>
        
        <label for="quantity">Quantity:</label><br>
        <input type="number" id="quantity" name="quantity"><br><br>

        <input type="submit" value="Buy Stock">
    </form>
</body>
</html>


Ensure you have the MySQL JDBC driver in your classpath and replace `"your_database"`, `"username"`, and `"password"` with your actual database details.