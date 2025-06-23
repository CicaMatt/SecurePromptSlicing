import java.sql.*;
import javax.servlet.http.*;
public class BuyStock extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String stock_name = request.getParameter("stock_name");
        int stock_quantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = request.getSession().getAttribute("username").toString();
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
            String sql = "INSERT INTO buy (stock_name, stock_quantity, username) VALUES (?, ?, ?)";
            PreparedStatement ps = con.prepareStatement(sql);
            ps.setString(1, stock_name);
            ps.setInt(2, stock_quantity);
            ps.setString(3, username);
            int n = ps.executeUpdate();
            if (n > 0) {
                response.sendRedirect("stocks.jsp");
            } else {
                response.sendRedirect("buyStock.jsp");
            }
        } catch (Exception e) {}
    }
}