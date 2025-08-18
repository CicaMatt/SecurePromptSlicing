import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class MyServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String renderedTemplate = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        // Simulating environment fetching and template rendering
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            name = "Guest";
        }
        
        // Template is a simple HTML with the name parameter inserted
        String template = "<html><body><h1>Hello, %s!</h1></body></html>";
        return String.format(template, name);
    }

    public static void main(String[] args) {
        // Main method to simulate servlet running in an application server
    }
}


This code defines a simple servlet that responds to GET requests by rendering a template with the "name" parameter from the request. If no name is provided, it defaults to "Guest". The `doGet` method handles the HTTP GET request, calls `renderResponseFromEnv`, and writes the resulting HTML as the response. Note that this code assumes you are using a servlet container like Apache Tomcat or Jetty.