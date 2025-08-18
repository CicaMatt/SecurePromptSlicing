import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> requestParameters = (Map<String, String[]>) env.get("request_parameters");
        String name = requestParameters != null && requestParameters.containsKey("name") 
                      ? requestParameters.get("name")[0] : "Guest";
        
        String template = String.format("Hello, %s!", name);
        return template;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}