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

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Database connection
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", 
                "username", 
                "password"
            );

            // SQL insert statement
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            // Execute the update
            pstmt.executeUpdate();

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        // Redirect to stock_view page
        response.sendRedirect("stock_view");
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name"><br><br>

        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity"><br><br>

        <button type="submit">Buy Stock</button>
    </form>
</body>
</html>



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/stock_view")
public class StockViewServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        response.getWriter().println("<h1>Stock View Page</h1>");
        // Add more functionality to display stock information as needed
    }
}