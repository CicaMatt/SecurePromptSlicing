import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    private static final String TEMPLATE_NAME = "template.html";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HashMap<String, Object> env = new HashMap<>();
        renderResponseFromEnv(request, response, env);
    }

    private void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, HashMap<String, Object> env) throws IOException {
        String name = request.getParameter("name");
        String template = (String) env.get(TEMPLATE_NAME);

        if (template == null || template.isEmpty()) {
            template = "<html><body><p>Hello, <span th:text=\"${name}\">Name</span></p></body></html>";
        }

        String renderedTemplate = renderTemplate(template, name);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderTemplate(String template, String name) {
        return template.replace("${name}", (name != null && !name.isEmpty()) ? name : "Guest");
    }
}