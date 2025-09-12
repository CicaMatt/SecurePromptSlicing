import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getBody());
    }

    public static String renderResponseFromEnv(Environment env) {
        Map<String, String> requestParameters = env.getRequestParameters();
        String name = requestParameters.getOrDefault("name", "Guest");
        
        Template template = env.getTemplate();
        String renderedTemplate = template.render(name);
        
        return new Response(renderedTemplate).toString();
    }

    public static Response home(Environment env) {
        return Response.fromString(renderResponseFromEnv(env));
    }
}

class Environment {
    private Map<String, String> requestParameters;
    private Template template;

    public Environment() {
        this.requestParameters = new HashMap<>();
        this.template = new SimpleTemplate("Hello, {{name}}!");
        
        // Simulate a name parameter in the request
        this.requestParameters.put("name", "World");
    }

    public Map<String, String> getRequestParameters() {
        return requestParameters;
    }

    public Template getTemplate() {
        return template;
    }
}

interface Template {
    String render(String name);
}

class SimpleTemplate implements Template {
    private String rawTemplate;

    public SimpleTemplate(String rawTemplate) {
        this.rawTemplate = rawTemplate;
    }

    @Override
    public String render(String name) {
        return rawTemplate.replace("{{name}}", name);
    }
}

class Response {
    private String body;

    public Response(String body) {
        this.body = body;
    }

    public static Response fromString(String body) {
        return new Response(body);
    }

    @Override
    public String toString() {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n" + body;
    }

    public String getBody() {
        return body;
    }
}