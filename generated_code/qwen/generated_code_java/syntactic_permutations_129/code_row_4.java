import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Environment env) {
        String name = env.getRequest().getParameter("name");
        String template = env.getTemplate();
        String renderedTemplate = template.replace("${name}", name);
        return new Response(renderedTemplate);
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
    }
}

class Environment {
    private Request request;
    private String template;

    public Environment() {
        this.request = new Request();
        this.template = "Hello, ${name}!";
    }

    public Request getRequest() {
        return request;
    }

    public String getTemplate() {
        return template;
    }
}

class Request {
    private Map<String, String> parameters;

    public Request() {
        this.parameters = new HashMap<>();
        this.parameters.put("name", "World");
    }

    public String getParameter(String key) {
        return parameters.get(key);
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