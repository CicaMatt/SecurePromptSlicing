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

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdb", "username", "password");

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();

            response.sendRedirect("stock_view");
        } catch (Exception e) {
            e.printStackTrace();
            throw new ServletException("Database error occurred.");
        }
    }
}