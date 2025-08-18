import java.util.Map;

public class TemplateRenderer {

    public String renderResponseFromEnv(Map<String, Object> environment) {
        Map<String, String[]> requestParameters = (Map<String, String[]>) environment.get("request_parameters");
        String name = requestParameters.containsKey("name") ? requestParameters.get("name")[0] : "Guest";
        
        String template = (String) environment.get("template");
        
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}