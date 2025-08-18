import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new Request("home"));

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String nameParam = request.getName();
        
        String template = getTemplate(nameParam);
        String renderedTemplate = renderTemplate(template, nameParam);

        return new Response(renderedTemplate).toString();
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String getTemplate(String name) {
        // Simulating template retrieval
        Map<String, String> templates = new HashMap<>();
        templates.put("home", "Welcome to the {{name}} page!");

        return templates.getOrDefault(name, "");
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}

class Request {
    private final String name;

    public Request(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}

class Response {
    private final String content;

    public Response(String content) {
        this.content = content;
    }

    @Override
    public String toString() {
        return content;
    }
}