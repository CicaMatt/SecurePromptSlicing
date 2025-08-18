import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/BuyOrderServlet")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity;
        
        try {
            stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid quantity entered.");
            return;
        }
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        
        if (username == null || stockName == null || stockQuantity <= 0) {
            response.sendRedirect("error_page.html");
            return;
        }

        // Insert buy order logic here
        // For example, insert into a database or any other storage system

        // Redirect to profile page
        response.sendRedirect("profile.jsp?username=" + username);
    }
}



<!-- HTML Form for User Input -->
<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <form action="BuyOrderServlet" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br><br>
        
        <label for="stock_quantity">Quantity:</label>
        <input type="number" id="stock_quantity" name="stock_quantity" min="1" required><br><br>

        <button type="submit">Buy</button>
    </form>
</body>
</html>



<!-- profile.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>User Profile</title>
</head>
<body>
    <h1>Welcome, <%= request.getParameter("username") %>!</h1>
    <!-- Display user profile information here -->
</body>
</html>



<!-- error_page.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Error</title>
</head>
<body>
    <h1>There was an error processing your request.</h1>
    <p>Please check the details you entered and try again.</p>
    <a href="index.jsp">Go Back</a>
</body>
</html>