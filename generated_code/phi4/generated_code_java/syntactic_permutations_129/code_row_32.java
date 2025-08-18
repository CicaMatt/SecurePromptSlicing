import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String renderedTemplate = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        String name = request.getParameter("name");
        String template = "<html><body><h1>Hello, ${name}!</h1></body></html>";
        
        // Simple string replacement for demonstration
        return template.replace("${name}", name != null ? name : "Guest");
    }
}