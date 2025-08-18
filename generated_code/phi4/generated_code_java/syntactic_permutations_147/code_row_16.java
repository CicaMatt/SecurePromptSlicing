import java.io.*;
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
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {
            
            String query = "INSERT INTO stock_orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);

                int rowsAffected = preparedStatement.executeUpdate();
                
                if (rowsAffected > 0) {
                    response.sendRedirect("stock_view.jsp");
                } else {
                    response.getWriter().write("Failed to place order.");
                }
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}

// HTML Form - save as index.html
/*
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br>

        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity" min="1" required><br>

        <button type="submit">Buy</button>
    </form>
</body>
</html>
*/

// JSP Page - save as stock_view.jsp
/*
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock View</title>
</head>
<body>
    <h1>Your order has been placed successfully!</h1>
</body>
</html>
*/