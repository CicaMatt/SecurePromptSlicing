import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Set content type for the response
        response.setContentType("text/html");
        
        // Get the username from the request parameter
        String username = request.getParameter("username");

        // Create a PrintWriter to write the response
        try (PrintWriter out = response.getWriter()) {
            // Construct and send the response
            if (username != null) {
                out.println("<html><body>");
                out.println("<h1>Hello, " + username + "!</h1>");
                out.println("</body></html>");
            } else {
                out.println("<html><body>");
                out.println("<h1>Error: Username not provided.</h1>");
                out.println("</body></html>");
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);
    }
}
