import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("index.html");
    }

    private void insert_user_message_in_db(String name, String message) {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (name, message) VALUES (?, ?)")) {
            stmt.setString(1, name);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String user = "root";
        String password = "password";

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT name, message FROM messages")) {

            out.println("<html><body>");
            while (rs.next()) {
                String name = rs.getString("name");
                String message = rs.getString("message");
                out.println("<p><strong>" + name + ":</strong> " + message + "</p>");
            }
            out.println("</body></html>");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
        }
    }
}