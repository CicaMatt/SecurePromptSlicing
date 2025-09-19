import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.List;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("index.html");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: " + name + " - " + message);
        // Actual database insertion code would go here
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = get_user_messages_from_db();

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        for (String message : messages) {
            out.println("<p>" + message + "</p>");
        }
        out.println("</body></html>");
    }

    private List<String> get_user_messages_from_db() {
        // Dummy implementation for demonstration purposes
        return List.of("User1: Hello", "User2: Hi there!", "User1: How are you?");
        // Actual database retrieval code would go here
    }
}