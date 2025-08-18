import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/PostMessage")
public class PostMessageServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to main page
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to post message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabaseName", 
                "yourUsername", 
                "yourPassword"
            );

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            if (pstmt != null) {
                try { pstmt.close(); } catch (Exception e) {}
            }
            if (conn != null) {
                try { conn.close(); } catch (Exception e) {}
            }
        }
    }

    // Main method to handle GET requests for displaying messages
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabaseName", 
                "yourUsername", 
                "yourPassword"
            );

            String sql = "SELECT username, message FROM messages";
            pstmt = conn.prepareStatement(sql);
            rs = pstmt.executeQuery();

            StringBuilder messagesHtml = new StringBuilder("<html><body>");
            while (rs.next()) {
                String user = rs.getString("username");
                String msg = rs.getString("message");

                messagesHtml.append("<p>").append(user).append(": ").append(msg).append("</p>");
            }
            messagesHtml.append("</body></html>");

            response.setContentType("text/html");
            response.getWriter().write(messagesHtml.toString());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (rs != null) {
                try { rs.close(); } catch (Exception e) {}
            }
            if (pstmt != null) {
                try { pstmt.close(); } catch (Exception e) {}
            }
            if (conn != null) {
                try { conn.close(); } catch (Exception e) {}
            }
        }
    }
}


Make sure to replace `"yourDatabaseName"`, `"yourUsername"`, and `"yourPassword"` with your actual database details. Additionally, you will need a MySQL JDBC driver in your classpath for this code to run successfully.