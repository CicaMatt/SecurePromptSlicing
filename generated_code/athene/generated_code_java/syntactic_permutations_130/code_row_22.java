import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> requestParams = (Map<String, String[]>) env.get("request_params");
        String name = requestParams.getOrDefault("name", new String[]{"Guest"})[0];
        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "request_params", Map.of("name", new String[]{"John"}),
            "template", "Hello, {name}!"
        );

        System.out.println(home(env));
    }
}