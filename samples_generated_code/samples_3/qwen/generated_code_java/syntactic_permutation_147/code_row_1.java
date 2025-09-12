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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();
        } catch (Exception e) {
            throw new ServletException(e);
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<!-- index.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name"><br/>
    Quantity: <input type="number" name="quantity"><br/>
    <input type="submit" value="Submit Order">
</form>
</body>
</html>



<!-- stock_view.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
<h1>Your order has been placed successfully!</h1>
<a href="index.jsp">Place another order</a>
</body>
</html>