import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buyStock")
public class BuyStockServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String username = request.getParameter("username");
        String stockName = request.getParameter("stock_name");
        int stockQuantity;
        
        try {
            stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
            
            Connection conn = null;

            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/yourDatabaseName", "yourUsername", "yourPassword");

                String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(sql);

                pstmt.setString(1, username);
                pstmt.setString(2, stockName);
                pstmt.setInt(3, stockQuantity);

                int affectedRows = pstmt.executeUpdate();
                
                if (affectedRows > 0) {
                    response.sendRedirect("orderSuccess.jsp");
                } else {
                    response.sendRedirect("error.jsp");
                }
            } catch (Exception e) {
                throw new ServletException(e);
            } finally {
                try {
                    if (conn != null) conn.close();
                } catch (Exception e) {
                    // Log error
                }
            }
        } catch (NumberFormatException nfe) {
            response.sendRedirect("error.jsp");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        doPost(request, response);
    }
}
