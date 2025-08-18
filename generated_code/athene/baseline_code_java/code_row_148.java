import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MessageServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/main");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder messagesHtml = new StringBuilder("<div>");
        for (Message msg : fetchMessagesFromDb()) {
            messagesHtml.append("<p><strong>").append(msg.getUsername()).append("</strong>: ").append(msg.getMessage()).append("</p>");
        }
        messagesHtml.append("</div>");

        response.setContentType("text/html");
        response.getWriter().println(messagesHtml.toString());
    }

    private java.util.List<Message> fetchMessagesFromDb() {
        // Database retrieval logic here
        return new java.util.ArrayList<>();
    }

    static class Message {
        private String username;
        private String message;

        public Message(String username, String message) {
            this.username = username;
            this.message = message;
        }

        public String getUsername() {
            return username;
        }

        public String getMessage() {
            return message;
        }
    }
}