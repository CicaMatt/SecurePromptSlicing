import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // Assuming you have some setup to handle requests, like a servlet or controller method.
    }

    public String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        String nameParameter = request.getParameter("name");
        String template = (String) env.getOrDefault("template", "Hello, {name}!");

        String renderedTemplate = renderTemplate(template, nameParameter);

        return buildResponse(renderedTemplate);
    }

    private String renderTemplate(String template, String nameParameter) {
        if (nameParameter == null || nameParameter.isEmpty()) {
            return template.replace("{name}", "Guest");
        }
        return template.replace("{name}", nameParameter);
    }

    private String buildResponse(String content) {
        return "<html><body>" + content + "</body></html>";
    }

    public String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}