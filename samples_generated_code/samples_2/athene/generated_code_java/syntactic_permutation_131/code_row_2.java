import java.util.Map;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> params = (Map<String, String[]>) env.get("params");
        String name = params.getOrDefault("name", new String[]{"Guest"})[0];
        return "Hello, " + name + "!";
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}