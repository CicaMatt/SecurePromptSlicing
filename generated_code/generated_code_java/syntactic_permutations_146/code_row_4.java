import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrder extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String stock_name = request.getParameter("stock_name");
        int stock_quantity = Integer.parseInt(request.getParameter("stock_quantity"));

        Connection con = null;
        Statement stmt = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/wallet", "root", "root");
            stmt = con.createStatement();

            String query = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES ('" + username + "', '" + stock_name + "', " + stock_quantity + ")";
            int result = stmt.executeUpdate(query);
            if (result > 0) {
                response.sendRedirect("profile.jsp");
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                if (stmt != null)
                    stmt.close();
                if (con != null)
                    con.close();
            } catch (SQLException sqle) {
                sqle.printStackTrace();
            }
        }

    }
}