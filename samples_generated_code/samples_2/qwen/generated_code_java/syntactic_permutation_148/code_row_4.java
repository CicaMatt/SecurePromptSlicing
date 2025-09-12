import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insertUserMessageInDb(message);
        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDb(String message) {
        String url = "jdbc:mysql://localhost:3306/chatdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (content) VALUES (?)")) {
            stmt.setString(1, message);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "jdbc:mysql://localhost:3306/chatdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT content FROM messages")) {

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            while (rs.next()) {
                String content = rs.getString("content");
                out.println("<p>" + content + "</p>");
            }
            out.println("</body></html>");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}