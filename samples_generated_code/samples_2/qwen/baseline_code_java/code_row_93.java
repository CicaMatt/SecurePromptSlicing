import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        String quantityStr = request.getParameter("quantity");
        int quantity = Integer.parseInt(quantityStr);

        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            stmt.executeUpdate();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<!-- stock_form.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        Stock Name: <input type="text" name="stockName"><br>
        Quantity: <input type="number" name="quantity"><br>
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
    <h1>Your order has been submitted!</h1>
    <a href="stock_form.html">Place another order</a>
</body>
</html>