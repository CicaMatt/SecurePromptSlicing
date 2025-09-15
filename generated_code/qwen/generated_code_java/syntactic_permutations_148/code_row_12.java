import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.List;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy method to simulate database insertion
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = getMessagesFromDb();

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        for (String message : messages) {
            out.println("<p>" + message + "</p>");
        }
        out.println("</body></html>");
    }

    private List<String> getMessagesFromDb() {
        // Dummy method to simulate database retrieval
        return List.of("Message 1", "Message 2", "Message 3");
    }
}
