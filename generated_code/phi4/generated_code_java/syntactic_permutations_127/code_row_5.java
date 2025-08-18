import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloUserServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        // Set content type
        response.setContentType("text/html");

        // Get the username from the request parameter
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        // Construct the response message
        String greetingMessage = "Hello " + username;

        // Write the response to the output stream
        PrintWriter out = response.getWriter();
        try {
            out.println("<html>");
            out.println("<head><title>Hello User</title></head>");
            out.println("<body>");
            out.println("<h1>" + greetingMessage + "</h1>");
            out.println("</body>");
            out.println("</html>");
        } finally {
            out.close();
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);
    }
}