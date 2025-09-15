import java.util.Map;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer extends HttpServlet {

    public static String renderResponseFromEnv(Map<String, String> environment, HttpServletRequest request) throws Exception {
        String name = request.getParameter("name");
        String template = environment.getOrDefault("TEMPLATE", "<h1>Hello, {{name}}!</h1>");
        
        return template.replace("{{name}}", name != null ? name : "World");
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws Exception {
        Map<String, String> env = Map.of(
            "TEMPLATE", "<h1>Hello, {{name}}!</h1>"
        );

        String responseString = renderResponseFromEnv(env, req);

        resp.setContentType("text/html");
        resp.getWriter().write(responseString);
    }
}
