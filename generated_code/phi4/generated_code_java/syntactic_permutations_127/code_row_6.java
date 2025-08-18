import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Set the content type of the response
        response.setContentType("text/plain");

        // Retrieve the username from the request parameter
        String username = request.getParameter("username");
        
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        // Construct the response message
        String greetingMessage = "Hello " + username;

        // Write the response to the response output stream
        PrintWriter out = response.getWriter();
        try {
            out.println(greetingMessage);
        } finally {
            out.close();  // Ensure the output stream is closed after use
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);  // Handle POST requests with the same logic as GET requests
    }
}