import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        try {
            insert_user_message_in_db(name, message);
        } catch (Exception e) {
            throw new ServletException(e);
        }

        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String name, String message) throws Exception {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password");
            stmt = conn.prepareStatement("INSERT INTO messages (name, message) VALUES (?, ?)");
            stmt.setString(1, name);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } finally {
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        StringBuilder messagesHtml = new StringBuilder("<div>");
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password")) {
            PreparedStatement stmt = conn.prepareStatement("SELECT name, message FROM messages");
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                String name = rs.getString("name");
                String message = rs.getString("message");
                messagesHtml.append("<p><strong>").append(name).append(":</strong> ").append(message).append("</p>");
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }

        messagesHtml.append("</div>");

        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println(messagesHtml.toString());
    }
}