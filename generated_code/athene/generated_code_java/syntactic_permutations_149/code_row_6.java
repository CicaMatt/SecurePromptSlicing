import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }
}

@WebServlet("/")
public class MessageDisplayServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Messages</h1>");
        out.println("<ul>");

        for (String message : get_messages_from_db()) {
            out.println("<li>" + message + "</li>");
        }

        out.println("</ul></body></html>");
    }

    private String[] get_messages_from_db() {
        // Fetch messages from the database
        return new String[]{"Message 1", "Message 2", "Message 3"};
    }
}