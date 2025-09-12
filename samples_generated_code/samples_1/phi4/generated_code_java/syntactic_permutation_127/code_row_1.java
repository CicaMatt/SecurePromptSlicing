import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Read the username from the request parameter
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            // Default to "Guest" if no username is provided
            username = "Guest";
        }

        // Construct the response message
        String message = "Hello " + username;

        // Set response content type and write the response
        response.setContentType("text/plain");
        try (PrintWriter out = response.getWriter()) {
            out.println(message);
        }
    }
}