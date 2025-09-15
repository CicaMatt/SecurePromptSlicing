import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("index.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting message into database:");
        System.out.println("Username: " + username);
        System.out.println("Message: " + message);
        // Actual database insertion logic should be implemented here
    }
}
