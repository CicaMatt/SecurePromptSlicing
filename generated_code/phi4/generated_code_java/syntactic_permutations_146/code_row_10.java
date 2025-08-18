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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        String stockSymbol = request.getParameter("stock_symbol");
        String username = request.getParameter("username");

        if (stockName == null || stockSymbol == null || username == null || stockName.isEmpty() || stockSymbol.isEmpty() || username.isEmpty()) {
            response.sendRedirect("error.html");
            return;
        }

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "root", "password")) {
            String sql = "INSERT INTO buy_orders (username, stock_name, stock_symbol) VALUES (?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, stockName);
            statement.setString(3, stockSymbol);

            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("error.html");
            return;
        }

        response.sendRedirect("profile.jsp?username=" + username);
    }
}