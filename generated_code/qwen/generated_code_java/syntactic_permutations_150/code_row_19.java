import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insert_user_message_in_db(message);
        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting message into database: " + message);
        // Actual database insertion logic should be implemented here
    }
}
