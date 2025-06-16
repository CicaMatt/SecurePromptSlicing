package view;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import model.*;
import util.DbConn;

public class buy_order extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
            String username = (String)request.getParameter("username");
            String isbn = (String)request.getParameter("isbn");
            String title = (String)request.getParameter("title");
            int quantity = Integer.parseInt(request.getParameter("quantity"));
            DbConn db = new DbConn();
            Connection conn = db.getConnection();
            PreparedStatement ps = null;
            try {
                ps = conn.prepareStatement("INSERT INTO buy_order (username, isbn, title, quantity) VALUES (?, ?, ?, ?)");
                ps.setString(1, username);
                ps.setString(2, isbn);
                ps.setString(3, title);
                ps.setInt(4, quantity);
                ps.executeUpdate();
            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                if (ps != null) {
                    try {
                        ps.close();
                    } catch (SQLException ex) {
                        ex.printStackTrace();
                    }
                }
                db.closeConnection(conn);
            }
            response.sendRedirect("stock_view");
        }
}