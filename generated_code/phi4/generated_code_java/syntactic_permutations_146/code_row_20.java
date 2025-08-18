import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/BuyStock")
public class BuyStockServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stockName");
        int stock_quantity = Integer.parseInt(request.getParameter("quantity"));
        String username = (String) request.getSession().getAttribute("username");

        // Simulate inserting the buy order into a database
        // For example: insertBuyOrder(username, stock_name, stock_quantity);

        response.sendRedirect("/profile.jsp");  // Redirect to profile page
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("buyStockForm.html").forward(request, response);
    }
}



<!-- buyStockForm.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <form action="BuyStock" method="post">
        <label for="stockName">Stock Name:</label>
        <input type="text" id="stockName" name="stockName" required><br>

        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" min="1" required><br>

        <button type="submit">Buy</button>
    </form>
</body>
</html>



<!-- profile.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Profile Page</title>
</head>
<body>
    <h1>Welcome, <%= request.getSession().getAttribute("username") %></h1>
    <p>Your buy order has been processed.</p>
</body>
</html>