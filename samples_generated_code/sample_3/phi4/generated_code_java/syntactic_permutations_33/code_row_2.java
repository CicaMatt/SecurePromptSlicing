import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        
        if (url != null && url.contains("example.com")) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL. Only example.com is allowed.");
        }
    }

    public static void main(String[] args) throws Exception {
        // This part assumes you are using a server like Tomcat to deploy the servlet.
        // In a real-world scenario, this would be handled by your web server's startup process.

        javax.servlet.ServletContext context = new org.apache.catalina.core.StandardContext();
        RedirectServlet servlet = new RedirectServlet();
        
        javax.servlet.ServletConfig config = context.createServletConfig(servlet.getClass().getName());
        servlet.init(config);
    }
}


**Note**: This code assumes you are deploying it in a servlet container like Apache Tomcat. The `@WebServlet` annotation is used to define the URL pattern, and the `doGet` method handles GET requests for that URL pattern.

For this to run, you need to have a web server setup (like Apache Tomcat) and include necessary libraries for servlets in your classpath or build path (typically included when setting up a Java EE project).