import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
        // For example:
        // try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
        //     String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        //     PreparedStatement stmt = conn.prepareStatement(sql);
        //     stmt.setString(1, username);
        //     stmt.setString(2, message);
        //     stmt.executeUpdate();
        // } catch (SQLException e) {
        //     e.printStackTrace();
        // }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Main Page</h1>");
        out.println("<form action='post' method='post'>");
        out.println("Username: <input type='text' name='username'><br><br>");
        out.println("Message: <textarea name='message'></textarea><br><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}