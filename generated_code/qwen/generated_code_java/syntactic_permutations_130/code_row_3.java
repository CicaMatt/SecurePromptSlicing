import java.util.HashMap;
import java.util.Map;

class Environment {
    private Map<String, String> requestParams = new HashMap<>();
    private Map<String, String> templates = new HashMap<>();

    public Environment() {
        // Example template setup
        this.templates.put("home", "<html><body>Hello, {{name}}!</body></html>");
    }

    public void setRequestParam(String key, String value) {
        requestParams.put(key, value);
    }

    public String getRequestParam(String key) {
        return requestParams.getOrDefault(key, "");
    }

    public String getTemplate(String name) {
        return templates.getOrDefault(name, "");
    }
}

public class Response {
    private final String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }

    @Override
    public String toString() {
        return content;
    }
}

public class Application {

    public static Response render_response_from_env(Environment env) {
        String name = env.getRequestParam("name");
        String template = env.getTemplate("home");
        String renderedContent = template.replace("{{name}}", name);
        return new Response(renderedContent);
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        env.setRequestParam("name", "World");
        Response response = home(env);
        System.out.println(response);
    }
}