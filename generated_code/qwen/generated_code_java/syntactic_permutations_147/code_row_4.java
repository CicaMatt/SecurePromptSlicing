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
        
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");
            
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, quantity);
            
            preparedStatement.executeUpdate();
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException("Database error", e);
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        
        response.sendRedirect("stock_view.jsp");
    }
}



<!-- stock_view.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Stock View</title>
</head>
<body>
    <h1>Stock Orders</h1>
    <p>Your order has been successfully placed.</p>
    <a href="index.jsp">Place another order</a>
</body>
</html>



<!-- index.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Buy Stock</title>
</head>
<body>
    <h1>Buy Stock</h1>
    <form action="buy_order" method="post">
        <label for="stockName">Stock Name:</label>
        <input type="text" id="stockName" name="stockName" required><br><br>
        
        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" required><br><br>
        
        <input type="submit" value="Submit">
    </form>
</body>
</html>