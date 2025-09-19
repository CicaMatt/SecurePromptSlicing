import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String renderedTemplate = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        String name = request.getParameter("name");
        
        // For simplicity, the template is hardcoded. In a real-world scenario, this might be loaded from a file or database.
        String template = "<html><body>Hello, %s!</body></html>";
        
        return String.format(template, name != null ? name : "Guest");
    }
}


To run this code:

1. Ensure you have a servlet container like Apache Tomcat installed and set up.
2. Place the above Java class in your web application's `src` directory.
3. Update your `web.xml` or use annotations (as shown) to map the servlet URL pattern if necessary.
4. Build and deploy the project to your servlet container.
5. Access `http://localhost:8080/yourAppName/home?name=YourName` in a web browser.