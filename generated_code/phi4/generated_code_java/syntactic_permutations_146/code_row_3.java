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

@WebServlet("/BuyStock")
public class BuyStockServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");

        try {
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", 
                "yourusername", 
                "yourpassword"
            );

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, stockName);
            statement.setInt(3, stockQuantity);

            statement.executeUpdate();

            response.sendRedirect("profile.jsp");
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }
    }
}
