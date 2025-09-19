import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
    }

    public static Response render_response_from_env(Environment env) {
        Request request = env.getRequest();
        String name = request.getParameter("name");
        Template template = env.getTemplate();
        String renderedContent = template.render(name);
        return new Response(renderedContent);
    }
}

class Environment {
    private final Request request;
    private final Template template;

    public Environment() {
        this.request = new Request();
        this.template = new Template();
    }

    public Request getRequest() {
        return request;
    }

    public Template getTemplate() {
        return template;
    }
}

class Request {
    private final Map<String, String> parameters;

    public Request() {
        this.parameters = new HashMap<>();
        this.parameters.put("name", "World"); // Example default value
    }

    public String getParameter(String key) {
        return parameters.getOrDefault(key, "");
    }
}

class Template {
    public String render(String name) {
        return "Hello, " + name + "!";
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