import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyStockServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        String username = request.getParameter("username");

        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockmarket", "user", "password");

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stockName);
            stmt.setInt(3, quantity);

            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                response.sendRedirect("profile.jsp");
            } else {
                response.sendRedirect("error.jsp");
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        } finally {
            try { if (stmt != null) stmt.close(); } catch (SQLException e) { /* ignored */ }
            try { if (conn != null) conn.close(); } catch (SQLException e) { /* ignored */ }
        }
    }
}