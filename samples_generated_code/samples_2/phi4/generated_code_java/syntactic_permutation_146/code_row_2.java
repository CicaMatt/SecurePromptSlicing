import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/buyOrder")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("quantity"));
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Establish connection
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database_name", 
                    "your_db_username", 
                    "your_db_password");

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            pstmt = conn.prepareStatement(sql);
            
            pstmt.setString(1, username);
            pstmt.setString(2, stockName);
            pstmt.setInt(3, stockQuantity);

            pstmt.executeUpdate();

            response.sendRedirect("profile.jsp");
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        } finally {
            if (pstmt != null) try { pstmt.close(); } catch (SQLException e) {}
            if (conn != null) try { conn.close(); } catch (SQLException e) {}
        }
    }
}


Make sure to replace `"your_database_name"`, `"your_db_username"`, and `"your_db_password"` with your actual database details. Additionally, ensure that the `profile.jsp` exists for redirection after a successful buy order insertion.