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
        Map<String, String> requestParameters = env.getRequest().getParameters();
        String name = requestParameters.get("name");
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
    private Map<String, String> parameters;

    public Request() {
        parameters = new HashMap<>();
        parameters.put("name", "World"); // Default name for demonstration
    }

    public Map<String, String> getParameters() {
        return parameters;
    }
}

class Template {
    private static final String TEMPLATE_FORMAT = "Hello, %s!";

    public String render(String name) {
        return String.format(TEMPLATE_FORMAT, name);
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