import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MessageServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/messages_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT username, message FROM user_messages";
            stmt = conn.prepareStatement(sql);
            rs = stmt.executeQuery();

            StringBuilder messagesHtml = new StringBuilder("<h1>Messages</h1><ul>");
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messagesHtml.append("<li>").append(username).append(": ").append(message).append("</li>");
            }
            messagesHtml.append("</ul>");

            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println(messagesHtml.toString());
            response.getWriter().println("<form action=\"/post\" method=\"post\">");
            response.getWriter().println("Username: <input type=\"text\" name=\"username\"><br>");
            response.getWriter().println("Message: <input type=\"text\" name=\"message\"><br>");
            response.getWriter().println("<input type=\"submit\" value=\"Submit\">");
            response.getWriter().println("</form>");
            response.getWriter().println("</body></html>");

        } catch (SQLException e) {
            throw new ServletException(e);
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException e) { e.printStackTrace(); }
            try { if (stmt != null) stmt.close(); } catch (SQLException e) { e.printStackTrace(); }
            try { if (conn != null) conn.close(); } catch (SQLException e) { e.printStackTrace(); }
        }
    }

    @WebServlet("/post")
    public static class PostMessageServlet extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String message = request.getParameter("message");

            insert_user_message_in_db(username, message);

            response.sendRedirect("/");
        }

        private void insert_user_message_in_db(String username, String message) {
            Connection conn = null;
            PreparedStatement stmt = null;

            try {
                conn = DriverManager.getConnection(DB_URL, USER, PASS);
                String sql = "INSERT INTO user_messages (username, message) VALUES (?, ?)";
                stmt = conn.prepareStatement(sql);
                stmt.setString(1, username);
                stmt.setString(2, message);
                stmt.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            } finally {
                try { if (stmt != null) stmt.close(); } catch (SQLException e) { e.printStackTrace(); }
                try { if (conn != null) conn.close(); } catch (SQLException e) { e.printStackTrace(); }
            }
        }
    }

    public void init() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}