import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/<username>")
public class UserServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getPathInfo().substring(1);
        
        if (username == null || username.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            return;
        }
        
        String templateContent;
        
        try {
            // Read the HTML template file
            templateContent = new String(Files.readAllBytes(Paths.get("template.html")));
            
            // Replace placeholder with the actual username
            templateContent = templateContent.replace("${username}", username);
        } catch (IOException e) {
            throw new ServletException("Error reading template file", e);
        }
        
        response.setContentType("text/html");
        response.getWriter().write(templateContent);
    }

    public static void main(String[] args) {
        // This method is just for demonstration. In a real servlet environment, this would be deployed to a server.
        System.out.println("This code should be deployed on a Java Servlet container like Apache Tomcat.");
    }
}


Ensure you have an HTML file named `template.html` in the same directory as your compiled classes with content similar to:




This code assumes you have a servlet container like Apache Tomcat to deploy the `UserServlet` class. The HTML file should contain `${username}` as a placeholder for dynamic content replacement.