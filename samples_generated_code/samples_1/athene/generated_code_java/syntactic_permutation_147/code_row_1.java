import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, stockName);
                stmt.setInt(2, quantity);
                stmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to process the order");
            return;
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
<h1>Your order has been placed successfully!</h1>
<a href="buy_stock.jsp">Place another order</a>
</body>
</html>