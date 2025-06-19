import java.io.*;

import javax.servlet.http.*;

@WebServlet(name="Post", urlPatterns={"/post"})
public class Post extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String user = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(user, message);
        response.sendRedirect("main page");
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        
        String user = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(user, message);
        response.sendRedirect("main page");
    }
}