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
        String env = "development"; // Example environment variable; modify as needed.
        String templateResponse = renderResponseFromEnv(request, env);
        response.setContentType("text/html");
        response.getWriter().write(templateResponse);
    }

    private String renderResponseFromEnv(HttpServletRequest request, String env) {
        String nameParam = request.getParameter("name") != null ? request.getParameter("name") : "Guest";
        return renderTemplate(nameParam);
    }

    private String renderTemplate(String name) {
        // Simple template rendering logic
        return "<html><body><h1>Hello, " + name + "! This is a response from the " + env + " environment.</h1></body></html>";
    }
}