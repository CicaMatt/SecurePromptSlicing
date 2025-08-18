import java.util.Map;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> requestParams = (Map<String, String[]>) env.get("request_params");
        String name = requestParams.getOrDefault("name", new String[]{"Guest"})[0];
        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}