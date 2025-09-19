import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "<html><body>Hello, {{name}}!</body></html>");
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Map<String, Object> env) {
        String name = (String) env.getOrDefault("name", "Guest");
        String template = (String) env.get("template");
        String renderedContent = template.replace("{{name}}", name);
        return new Response(renderedContent);
    }

    public static Response home(Map<String, Object> env) {
        return render_response_from_env(env);
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