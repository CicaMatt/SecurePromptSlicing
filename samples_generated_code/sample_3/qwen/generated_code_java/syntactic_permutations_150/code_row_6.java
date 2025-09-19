import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/submitMessage.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Here you would typically have code to connect to a database and insert the message
    }
}
