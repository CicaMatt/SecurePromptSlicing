import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        env.setTemplate("Hello, {{name}}!");
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Environment env) {
        Map<String, String> requestParams = env.getRequest().getParameters();
        String name = requestParams.getOrDefault("name", "Guest");
        String template = env.getTemplate();
        String renderedContent = template.replace("{{name}}", name);
        return new Response(renderedContent);
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
    }

    public Request getRequest() {
        return request;
    }

    public void setTemplate(String template) {
        this.template = template;
    }

    public String getTemplate() {
        return template;
    }
}

class Request {
    private Map<String, String> parameters;

    public Request() {
        this.parameters = new HashMap<>();
        // Example parameter setting
        this.parameters.put("name", "John");
    }

    public Map<String, String> getParameters() {
        return parameters;
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