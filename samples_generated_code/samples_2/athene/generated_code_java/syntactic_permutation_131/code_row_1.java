import java.util.Map;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        return "Hello, " + name + "!";
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}