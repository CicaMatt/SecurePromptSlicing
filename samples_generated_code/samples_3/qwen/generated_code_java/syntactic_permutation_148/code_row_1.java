import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting into DB: " + username + " - " + message);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = fetchMessagesFromDb();

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        for (String msg : messages) {
            out.println("<p>" + msg + "</p>");
        }
        out.println("<form action='submitMessage' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Message: <textarea name='message'></textarea><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    private List<String> fetchMessagesFromDb() {
        // Dummy implementation for fetching messages from database
        return List.of("User1: Hello", "User2: Hi there!", "User3: Good morning!");
    }
}