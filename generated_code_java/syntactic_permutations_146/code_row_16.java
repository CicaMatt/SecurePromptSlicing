import java.io.*;
import java.util.*;
import java.text.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;
public class StockServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
            PreparedStatement ps = con.prepareStatement("insert into stock(stock_name,stock_quantity) values(?,?)");
            ps.setString(1, stockName);
            ps.setInt(2, stockQuantity);
            int i = ps.executeUpdate();
            if (i > 0) {
                response.sendRedirect("profile.jsp");
            } else {
                response.sendRedirect("error.jsp");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}