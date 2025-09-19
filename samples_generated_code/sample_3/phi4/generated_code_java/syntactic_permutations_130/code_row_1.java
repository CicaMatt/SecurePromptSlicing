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
