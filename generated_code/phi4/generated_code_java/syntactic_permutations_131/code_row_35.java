import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static String renderResponseFromEnv(Environment env, Map<String, String> requestParams) {
        String name = requestParams.getOrDefault("name", "Guest");
        String template = env.getTemplate();

        return String.format(template, name);
    }

    public static Response home(Environment env) {
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "John Doe");

        String renderedContent = renderResponseFromEnv(env, requestParams);
        return new Response(renderedContent);
    }
}

class Environment {
    private String template;

    public Environment() {
        this.template = "<html><body><h1>Hello, %s!</h1></body></html>";
    }

    public String getTemplate() {
        return template;
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