import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insertUserMessageInDb(message);
        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String message) {
        // Database insertion logic here
    }
}
