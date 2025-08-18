import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> requestParams = (Map<String, String[]>) env.get("request_params");
        String name = requestParams != null && requestParams.containsKey("name") ? requestParams.get("name")[0] : "Guest";
        String template = env.get("template").toString();
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}