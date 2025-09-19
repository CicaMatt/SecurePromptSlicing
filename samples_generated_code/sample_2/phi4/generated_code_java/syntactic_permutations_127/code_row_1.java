import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HelloServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Set the content type to HTML
        response.setContentType("text/html");
        
        // Get the PrintWriter object from response to write data
        PrintWriter out = response.getWriter();
        
        try {
            // Read the username parameter from the request
            String username = request.getParameter("username");

            if (username == null || username.isEmpty()) {
                username = "User";
            }

            // Construct and send the response
            out.println("<html><body>");
            out.println("<h1>Hello " + username + "</h1>");
            out.println("</body></html>");

        } finally {
            out.close();
        }
    }
}