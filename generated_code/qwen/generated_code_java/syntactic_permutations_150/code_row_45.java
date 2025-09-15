import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(name, message);
        
        response.sendRedirect("/main.jsp");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Placeholder for database insertion logic
        System.out.println("Inserting into database: Name - " + name + ", Message - " + message);
    }
}
