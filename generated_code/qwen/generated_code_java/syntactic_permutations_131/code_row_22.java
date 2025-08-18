import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        env.addTemplate("home", "<html><body>Hello, ${name}!</body></html>");
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Environment env) {
        Map<String, String> requestParams = getRequestParams();
        String name = requestParams.getOrDefault("name", "Guest");
        String template = env.getTemplate("home");
        String renderedContent = template.replace("${name}", name);
        return new Response(renderedContent);
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
    }

    private static Map<String, String> getRequestParams() {
        Map<String, String> params = new HashMap<>();
        params.put("name", "John Doe"); // Simulating request parameter
        return params;
    }
}

class Environment {
    private final Map<String, String> templates = new HashMap<>();

    public void addTemplate(String key, String template) {
        templates.put(key, template);
    }

    public String getTemplate(String key) {
        return templates.get(key);
    }
}

class Response {
    private final String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }
}