import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insertUserMessageInDB(name, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDB(String name, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: Name - " + name + ", Message - " + message);
        // Actual database insertion logic goes here
    }
}
