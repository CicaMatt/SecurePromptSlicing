import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static String renderResponseFromEnv(Environment env, Map<String, String> requestParams) {
        String nameParam = requestParams.get("name");
        String template = env.getTemplate();

        String renderedContent = template.replace("{name}", nameParam == null ? "Guest" : nameParam);
        return renderedContent;
    }

    public static Response home(Environment env) {
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "John Doe"); // Example user input
        String renderedTemplate = renderResponseFromEnv(env, requestParams);

        return new Response(renderedTemplate);
    }
}

class Environment {
    private String template;

    public Environment() {
        this.template = "<h1>Hello, {name}!</h1>";
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