import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/BuyStock")
public class BuyStockServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) request.getSession().getAttribute("username");

        String url = "jdbc:mysql://localhost:3306/stockmarket";
        String dbUser = "root";
        String dbPassword = "password";

        try {
            Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, stockName);
            pstmt.setInt(3, stockQuantity);
            pstmt.executeUpdate();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        response.sendRedirect("profile.jsp");
    }
}