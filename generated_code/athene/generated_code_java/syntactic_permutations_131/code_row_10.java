import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> environment) {
        UserRequest request = getUserRequest();
        String template = (String) environment.get("template");
        String renderedTemplate = renderTemplate(template, request);
        return createResponse(renderedTemplate);
    }

    private static UserRequest getUserRequest() {
        // Simulate getting user request
        return new UserRequest();
    }

    private static String renderTemplate(String template, UserRequest request) {
        // Simulate rendering the template with data from the request
        return template + " - rendered with data: " + request.getData();
    }

    private static String createResponse(String renderedTemplate) {
        // Create a response with the rendered template
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}

class UserRequest {
    public String getData() {
        // Simulate user request data
        return "user data";
    }
}