import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Dummy implementation. Replace with actual database insertion logic.
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}
