import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Actual database insertion logic should be implemented here
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fetch messages from the database and set them as an attribute in the request
        String[] messages = fetch_messages_from_db(); // This method should return actual messages from the database

        request.setAttribute("messages", messages);
        RequestDispatcher dispatcher = request.getRequestDispatcher("displayMessages.jsp");
        dispatcher.forward(request, response);
    }

    private String[] fetch_messages_from_db() {
        // Dummy implementation for demonstration purposes
        return new String[]{"Message 1 from User A", "Message 2 from User B"};
        // Actual database fetching logic should be implemented here
    }
}
