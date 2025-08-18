import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        String name = request.getParameter("name");
        
        // Simulating template fetching and rendering
        String template = "Hello, %s!";
        String renderedTemplate = String.format(template, name);

        return renderedTemplate;
    }

    public static void home(Map<String, Object> env) throws IOException {
        String responseContent = renderResponseFromEnv(env);
        HttpServletResponse response = (HttpServletResponse) env.get("response");
        response.setContentType("text/plain");
        response.getWriter().write(responseContent);
    }
}