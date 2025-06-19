import java.io.*;
import javax.servlet.http.*;

public class PostMessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        
        RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
        rd.forward(request, response);
    }
}