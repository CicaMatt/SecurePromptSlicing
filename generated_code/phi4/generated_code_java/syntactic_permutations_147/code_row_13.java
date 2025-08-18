import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.RequestDispatcher;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockSymbol = request.getParameter("stock_symbol");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        try (Connection connection = getConnection()) {
            String sql = "INSERT INTO orders (stock_symbol, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockSymbol);
                statement.setInt(2, quantity);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }

        RequestDispatcher dispatcher = request.getRequestDispatcher("/stock_view");
        dispatcher.forward(request, response);
    }

    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        return DriverManager.getConnection(url, user, password);
    }
}

import java.io.IOException;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/index.jsp").forward(request, response);
    }
}



<!-- index.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <h1>Enter Order Details</h1>
    <form action="buy_order" method="post">
        Stock Symbol: <input type="text" name="stock_symbol"><br><br>
        Quantity: <input type="number" name="quantity"><br><br>
        <input type="submit" value="Submit Order">
    </form>
</body>
</html>



<!-- stock_view.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
    <h1>Order Submitted Successfully!</h1>
</body>
</html>


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure you have the MySQL JDBC driver in your project's classpath.