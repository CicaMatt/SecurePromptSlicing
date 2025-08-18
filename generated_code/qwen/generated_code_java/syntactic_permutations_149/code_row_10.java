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
    private static final String PASS = "";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.prepareStatement("SELECT message FROM messages ORDER BY id DESC");
            rs = stmt.executeQuery();

            StringBuilder messagesHtml = new StringBuilder("<html><body>");
            while (rs.next()) {
                messagesHtml.append("<p>").append(rs.getString("message")).append("</p>");
            }
            messagesHtml.append("<form action=\"/post\" method=\"post\">")
                        .append("<input type=\"text\" name=\"userMessage\" required>")
                        .append("<button type=\"submit\">Submit</button>")
                        .append("</form>")
                        .append("</body></html>");

            response.setContentType("text/html");
            response.getWriter().write(messagesHtml.toString());
        } catch (Exception e) {
            throw new ServletException(e);
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException se2) {}
            try { if (stmt != null) stmt.close(); } catch (SQLException se2) {}
            try { if (conn != null) conn.close(); } catch (SQLException se) {}
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("userMessage");
        insertUserMessageInDb(message);
        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String message) {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.prepareStatement("INSERT INTO messages (message) VALUES (?)");
            stmt.setString(1, message);
            stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try { if (stmt != null) stmt.close(); } catch (SQLException se2) {}
            try { if (conn != null) conn.close(); } catch (SQLException se) {}
        }
    }
}



<!-- Add this to your web.xml or equivalent annotations if using a newer servlet container -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>

    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/post</url-pattern>
    </servlet-mapping>
</web-app>