import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insertUserMessageInDb(username, message);
        
        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy method to represent database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        // Actual database code would go here
    }
}
