import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/BuyOrder")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");

        if (username == null || stockName == null || stockQuantity <= 0) {
            response.sendRedirect("error.jsp"); // Redirect to error page if validation fails
            return;
        }

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourdatabase", "root", "password");

            String query = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement ps = con.prepareStatement(query);
            ps.setString(1, username);
            ps.setString(2, stockName);
            ps.setInt(3, stockQuantity);

            int rowsAffected = ps.executeUpdate();
            if (rowsAffected > 0) {
                response.sendRedirect("profile.jsp"); // Redirect to profile page on success
            } else {
                response.sendRedirect("error.jsp"); // Redirect to error page on failure
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("error.jsp"); // Redirect to error page in case of exception
        }
    }
}