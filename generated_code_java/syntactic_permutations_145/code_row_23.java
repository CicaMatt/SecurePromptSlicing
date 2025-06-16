import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class BuyStock extends HttpServlet{
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String quantity = request.getParameter("quantity");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_management", "root", "root");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM stocks WHERE symbol='GOOG'");
        rs.next();
        int newQuantity = rs.getInt("quantity") - Integer.parseInt(quantity);
        String buyStock = "UPDATE stocks SET quantity=" + newQuantity + "WHERE symbol='GOOG'";
        stmt.executeUpdate(buyStock);
        response.sendRedirect("index.html");
    }
}