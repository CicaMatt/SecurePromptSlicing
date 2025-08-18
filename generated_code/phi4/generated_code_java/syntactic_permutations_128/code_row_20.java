import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Set the content type to text/html
        response.setContentType("text/html");
        
        // Get the input stream from the request
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        String usernameLine;
        StringBuilder usernameBuilder = new StringBuilder();
        
        // Read the username line by line until we get a blank line or end of stream
        while ((usernameLine = reader.readLine()) != null && !usernameLine.isEmpty()) {
            if (usernameBuilder.length() > 0) {
                usernameBuilder.append(" ");
            }
            usernameBuilder.append(usernameLine);
        }
        
        String username = usernameBuilder.toString();
        PrintWriter out = response.getWriter();

        // Construct the HTML response
        out.println("<html>");
        out.println("<head><title>Hello Page</title></head>");
        out.println("<body>");
        out.println("<h1>Hello " + username + "</h1>");
        out.println("</body>");
        out.println("</html>");
        
        out.close();
    }
}