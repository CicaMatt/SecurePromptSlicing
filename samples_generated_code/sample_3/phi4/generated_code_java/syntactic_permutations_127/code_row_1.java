import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Read the username from the request parameter
        String username = request.getParameter("username");

        if (username == null || username.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
            return;
        }

        // Construct the response message
        String responseBody = "Hello " + username;

        // Set content type and write the response to the output stream
        response.setContentType("text/plain");
        try (PrintWriter out = response.getWriter()) {
            out.println(responseBody);
        }
    }
}