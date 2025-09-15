import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Simulate database insertion
        System.out.println("Inserting into DB: User: " + username + ", Message: " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<html><head><title>Messages</title></head><body>");
        out.println("<h1>Messages</h1>");

        // Simulate fetching messages from the database
        String[] simulatedMessages = {
            "User1: Hello!",
            "User2: Hi there!",
            "User3: Welcome!"
        };

        for (String msg : simulatedMessages) {
            out.println("<p>" + msg + "</p>");
        }

        out.println("<h2>Submit a new message</h2>");
        out.println("<form method='post' action='/message'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Message: <input type='text' name='message'><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");

        out.println("</body></html>");
    }
}
