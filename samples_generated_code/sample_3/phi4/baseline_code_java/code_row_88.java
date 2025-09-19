import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/postMessage")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/index.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implement database insertion logic here
        // Example:
        // try (Connection connection = DriverManager.getConnection(...)) {
        //     PreparedStatement ps = connection.prepareStatement("INSERT INTO messages(username, message) VALUES (?, ?)");
        //     ps.setString(1, username);
        //     ps.setString(2, message);
        //     ps.executeUpdate();
        // } catch (SQLException e) {
        //     e.printStackTrace();
        // }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<!DOCTYPE html>");
        response.getWriter().println("<html><head><title>Main Page</title></head><body>");
        response.getWriter().println("<h1>Submit a Message</h1>");
        response.getWriter().println("<form action='postMessage' method='POST'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Message: <textarea name='message'></textarea><br>");
        response.getWriter().println("<input type='submit' value='Submit'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}
