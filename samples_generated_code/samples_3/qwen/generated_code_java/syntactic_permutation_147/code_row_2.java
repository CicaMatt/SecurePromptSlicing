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
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");
            PreparedStatement statement = connection.prepareStatement("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)");
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            statement.executeUpdate();
            response.sendRedirect("/success.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("/error.jsp");
        }
    }
}