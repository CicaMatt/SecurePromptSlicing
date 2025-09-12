import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stock_name");
        String stock_quantity_str = request.getParameter("stock_quantity");
        String username = (String) request.getSession().getAttribute("username");

        int stock_quantity;
        try {
            stock_quantity = Integer.parseInt(stock_quantity_str);
        } catch (NumberFormatException e) {
            response.sendRedirect("error.jsp?message=Invalid%20quantity");
            return;
        }

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockmarket", "user", "password");

            String sql = "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, stock_name);
            pstmt.setInt(3, stock_quantity);

            int rowsAffected = pstmt.executeUpdate();
            if (rowsAffected > 0) {
                response.sendRedirect("profile.jsp");
            } else {
                response.sendRedirect("error.jsp?message=Failed%20to%20insert%20order");
            }
        } catch (ClassNotFoundException | SQLException e) {
            response.sendRedirect("error.jsp?message=" + e.getMessage());
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}