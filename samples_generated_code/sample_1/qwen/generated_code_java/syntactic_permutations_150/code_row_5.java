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
        // Database logic to insert the message
        // This is a placeholder for actual database insertion code
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
    }
}
