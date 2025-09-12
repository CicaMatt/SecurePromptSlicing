import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/buyStock")
public class BuyStockServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        String username = request.getParameter("username");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, stockName);
                stmt.setInt(3, quantity);
                stmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("error.jsp");
            return;
        }

        response.sendRedirect("profile.jsp");
    }
}