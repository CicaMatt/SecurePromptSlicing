import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insertUserMessageInDB(name, message);

        response.sendRedirect("index.jsp");
    }

    private void insertUserMessageInDB(String name, String message) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

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
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT name, message FROM messages")) {

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();

            out.println("<html><head><title>Messages</title></head><body>");
            out.println("<h1>Messages</h1>");
            out.println("<form action='MessageServlet' method='post'>");
            out.println("Name: <input type='text' name='name'><br>");
            out.println("Message: <input type='text' name='message'><br>");
            out.println("<input type='submit' value='Submit'>");
            out.println("</form>");

            while (rs.next()) {
                String msgName = rs.getString("name");
                String msgContent = rs.getString("message");
                out.println("<p><strong>" + msgName + ":</strong> " + msgContent + "</p>");
            }

            out.println("</body></html>");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
