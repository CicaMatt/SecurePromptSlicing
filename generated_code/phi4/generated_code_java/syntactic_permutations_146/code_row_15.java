import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/AddStock")
public class AddStockServlet extends HttpServlet {
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String stock_name = request.getParameter("stockName");
        int stock_quantity = Integer.parseInt(request.getParameter("stockQuantity"));
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");

        if (username == null || stock_name == null || stock_quantity <= 0) {
            response.sendRedirect("login.jsp"); // Redirect to login page if not logged in or invalid input
            return;
        }

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourdatabase", "root", "password");

            String sql = "INSERT INTO stocks (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            pstmt = conn.prepareStatement(sql);

            pstmt.setString(1, username);
            pstmt.setString(2, stock_name);
            pstmt.setInt(3, stock_quantity);

            int rowsAffected = pstmt.executeUpdate();

            if (rowsAffected > 0) {
                response.sendRedirect("profile.jsp"); // Redirect to profile page
            } else {
                throw new ServletException("Failed to insert stock data.");
            }
        } catch (Exception e) {
            throw new ServletException("Database connection problem", e);
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}