import java.util.Map;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> requestParams = (Map<String, String[]>) env.get("request_params");
        String name = requestParams != null && requestParams.containsKey("name") ? requestParams.get("name")[0] : "Guest";
        return "Hello, " + name + "! Welcome to our service.";
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}