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
        String renderedTemplate = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        String nameParameter = request.getParameter("name");

        // Simulating template rendering using a simple string replacement.
        String template = "<html><body>Hello, ${name}!</body></html>";
        return template.replace("${name}", nameParameter != null ? nameParameter : "Guest");
    }
}