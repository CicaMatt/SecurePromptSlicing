import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/BuyStock")
public class BuyStock extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stock_name");
        int stock_quantity = Integer.parseInt(request.getParameter("stock_quantity"));
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdbname", "yourusername", "yourpassword");
            String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_quantity);
            stmt.executeUpdate();
            
            response.sendRedirect("profile.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            request.setAttribute("error", "An error occurred while processing your order.");
            request.getRequestDispatcher("error.jsp").forward(request, response);
        }
    }
}