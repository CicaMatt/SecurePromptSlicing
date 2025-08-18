import java.util.HashMap;
import java.util.Map;

public class Renderer {

    public static String render_response_from_env(Environment env) {
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World"); // Example name parameter

        Template template = env.getTemplate();
        return template.render(request);
    }

    public static Response home(Environment env) {
        return new Response(render_response_from_env(env));
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }
}

class Environment {
    public Template getTemplate() {
        return new Template();
    }
}

class Template {
    public String render(Map<String, Object> context) {
        String name = (String) context.get("name");
        return "Hello, " + name + "!";
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