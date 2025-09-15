import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Set the content type of the response
        response.setContentType("text/plain");

        // Get the username from the request parameter "username"
        String username = request.getParameter("username");

        // Construct the greeting message
        String greetingMessage = "Hello " + (username != null ? username : "User") + "!";

        // Write the greeting message to the response output stream
        try (PrintWriter out = response.getWriter()) {
            out.println(greetingMessage);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);
    }
}
