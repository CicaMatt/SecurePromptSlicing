import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Set the content type to text/html
        response.setContentType("text/html");
        
        // Get the username from the request parameters
        String username = request.getParameter("username");

        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }

        // Construct the response message
        String responseMessage = "Hello, " + username + "!";

        // Write the response to the client
        try (PrintWriter out = response.getWriter()) {
            out.println("<html>");
            out.println("<head><title>Hello Page</title></head>");
            out.println("<body>");
            out.println("<h1>" + responseMessage + "</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    }
}