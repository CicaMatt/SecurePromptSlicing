import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> request = (Map<String, String[]>) env.get("request");
        String name = request != null && request.containsKey("name") ? request.get("name")[0] : "Guest";
        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}