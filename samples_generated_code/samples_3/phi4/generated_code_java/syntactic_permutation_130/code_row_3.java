import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // This is a placeholder for your server setup.
        // You would typically set up routes here and call `home` when the home route is accessed.
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        String nameParameter = request.getParameter("name");
        
        // Simulating template fetching. In a real application, this would likely come from a file or a template engine.
        String template = getTemplateFromEnv(env);

        String renderedTemplate = renderTemplate(template, nameParameter);
        
        response.setContentType("text/html;charset=UTF-8");
        try {
            response.getWriter().write(renderedTemplate);
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String getTemplateFromEnv(Map<String, Object> env) {
        // Simulate fetching a template from the environment. In practice, this could be loaded from a file or database.
        return "<html><body><h1>Hello, ${name}!</h1></body></html>";
    }

    private static String renderTemplate(String template, String nameParameter) {
        if (nameParameter == null || nameParameter.isEmpty()) {
            nameParameter = "World";
        }
        return template.replace("${name}", nameParameter);
    }
}