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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }

        response.sendRedirect("stock_view");
    }
}

// HTML Form Example
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
        <input type="number" id="quantity" name="quantity" required><br>
        <button type="submit">Buy</button>
    </form>
</body>
</html>
*/