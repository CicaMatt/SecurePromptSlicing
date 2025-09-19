import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        
        response.sendRedirect(request.getContextPath() + "/submitMessage.html");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}

import java.io.*;

public class SubmitMessageForm extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        out.println("<html>");
        out.println("<head><title>Submit Message</title></head>");
        out.println("<body>");
        out.println("<h2>Submit a Message</h2>");
        out.println("<form action='post' method='post'>");
        out.println("Username: <input type='text' name='username'><br><br>");
        out.println("Message: <textarea name='message' rows='4' cols='50'></textarea><br><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
}