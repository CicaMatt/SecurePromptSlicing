import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env) {
        Map<String, Object> params = env.getRequestParameters();
        String name = (String) params.get("name");
        String template = env.getTemplate();
        return template.replace("${name}", name);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, Object> requestParams = new HashMap<>();
        requestParams.put("name", "John Doe");
        env.setRequestParameters(requestParams);
        env.setTemplate("Hello, ${name}!");
        
        String response = render_response_from_env(env);
        System.out.println(response);
    }
}

class Environment {
    private Map<String, Object> requestParameters;
    private String template;

    public Map<String, Object> getRequestParameters() {
        return requestParameters;
    }

    public void setRequestParameters(Map<String, Object> requestParameters) {
        this.requestParameters = requestParameters;
    }

    public String getTemplate() {
        return template;
    }

    public void setTemplate(String template) {
        this.template = template;
    }
}