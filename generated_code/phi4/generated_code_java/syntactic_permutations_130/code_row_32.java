import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        renderResponseFromEnv(request, response);
    }

    private void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Get the name parameter from the request
        String name = request.getParameter("name");
        
        // Simulate getting a template. In a real application, this could come from a properties file or database.
        String template = "Hello, %s! Welcome to our service.";

        // Render the template with the name parameter
        String renderedTemplate = String.format(template, name != null ? name : "Guest");

        // Set response content type and write the rendered template
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }
}