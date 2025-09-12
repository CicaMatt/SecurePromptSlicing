import java.io.IOException;
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

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) request.getSession().getAttribute("username");

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourdatabase", "yourusername", "yourpassword");

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);
            preparedStatement.setInt(3, stockQuantity);

            int rowsAffected = preparedStatement.executeUpdate();
            
            if (rowsAffected > 0) {
                response.sendRedirect("profile.jsp");
            } else {
                throw new RuntimeException("Failed to insert buy order.");
            }
        } catch (Exception e) {
            e.printStackTrace();
            // Handle exceptions appropriately in real applications
        } finally {
            if (preparedStatement != null) try { preparedStatement.close(); } catch (Exception e) {}
            if (connection != null) try { connection.close(); } catch (Exception e) {}
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }
}