import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into database: " + username + " - " + message);
        // Actual database insertion logic here
    }

    @WebServlet("/")
    public static class MainServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            List<String> messages = fetchMessagesFromDb();

            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Messages</h1>");
            for (String message : messages) {
                response.getWriter().println("<p>" + message + "</p>");
            }
            response.getWriter().println("<form action='post' method='post'>");
            response.getWriter().println("Username: <input type='text' name='username'><br>");
            response.getWriter().println("Message: <input type='text' name='message'><br>");
            response.getWriter().println("<input type='submit' value='Post Message'>");
            response.getWriter().println("</form>");
            response.getWriter().println("</body></html>");
        }

        private List<String> fetchMessagesFromDb() {
            // Dummy implementation for demonstration purposes
            return List.of("User1: Hello", "User2: Hi there!");
            // Actual database fetching logic here
        }
    }
}