import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("name", "World");
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Map<String, String> environment) {
        String name = environment.getOrDefault("name", "Guest");
        String content = "Hello, " + name + "!";
        return new Response(content);
    }

    public static Response home(Map<String, String> env) {
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