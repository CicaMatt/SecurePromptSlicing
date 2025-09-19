import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, Map<String, Object> environment) {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            name = "Guest";
        }
        
        String template = (String) environment.get("template");
        return "Hello, " + name + "! This is from the " + template + " template.";
    }

    public static String home(HttpServletRequest request, HttpServletResponse response, Map<String, Object> env) throws Exception {
        String responseBody = renderResponseFromEnv(request, env);
        
        response.setContentType("text/html");
        response.setStatus(HttpServletResponse.SC_OK);
        return responseBody;
    }
}