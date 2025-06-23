import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import javax.sql.*;
public class Servlet extends HttpServlet {
    private DataSource ds;
    public void init(ServletConfig config) throws ServletException {
        try {
            Context initCtx = new InitialContext();
            Context envCtx = (Context) initCtx.lookup("java:comp/env");
            ds = (DataSource) envCtx.lookup("jdbc/moderation");
        } catch (NamingException e) {
            throw new ServletException(e);
        }
    }
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        Connection db = null;
        Statement stmt = null;
        ResultSet rs = null;
        try {
            db = ds.getConnection();
            stmt = db.createStatement();
            String query = "SELECT is_moderator FROM users WHERE user_id=?";
            PreparedStatement ps = db.prepareStatement(query);
            ps.setInt(1, Integer.parseInt(request.getParameter("user_id")));
            rs = ps.executeQuery();
            if (rs.next()) {
                String result = "The user is a moderator";
                response.setContentType("text/plain");
                response.getWriter().println(result);
            } else {
                String result = "The user is not a moderator";
                response.setContentType("text/plain");
                response.getWriter().println(result);
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (db != null) db.close();
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        }
    }
}