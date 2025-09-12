import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
    }

    public static Response render_response_from_env(Environment env) {
        String name = env.getRequest().get("name");
        Template template = env.getTemplate();
        String renderedContent = template.render(name);
        return new Response(renderedContent);
    }
}

class Environment {
    private Request request;
    private Template template;

    public Environment() {
        this.request = new Request();
        // Simulate a template with name placeholder
        this.template = new Template("Hello, {name}!");
    }

    public Request getRequest() {
        return request;
    }

    public Template getTemplate() {
        return template;
    }
}

class Request {
    private Map<String, String> parameters;

    public Request() {
        this.parameters = new HashMap<>();
        // Simulate a parameter
        this.parameters.put("name", "John Doe");
    }

    public String get(String key) {
        return parameters.getOrDefault(key, "");
    }
}

class Template {
    private String content;

    public Template(String content) {
        this.content = content;
    }

    public String render(String name) {
        return content.replace("{name}", name);
    }
}

class Response {
    private String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }
}