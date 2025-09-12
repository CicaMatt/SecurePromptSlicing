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
    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/stocks";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = connect()) {
            if (conn != null) {
                String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, stockName);
                stmt.setInt(2, quantity);
                stmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        response.sendRedirect("stock_view");
    }
}