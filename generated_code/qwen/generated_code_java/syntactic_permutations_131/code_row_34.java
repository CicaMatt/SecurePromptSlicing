import java.util.HashMap;
import java.util.Map;

public class Renderer {

    public static String renderResponseFromEnv(Environment env) {
        Map<String, String> requestParams = env.getUserRequest();
        String name = requestParams.get("name");
        String template = env.getTemplate();
        String renderedTemplate = template.replace("{name}", name);
        return "HTTP/1.1 200 OK\n\n" + renderedTemplate;
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "World");
        env.setUserRequest(requestParams);
        env.setTemplate("Hello, {name}!");
        
        System.out.println(home(env));
    }
}

class Environment {
    private Map<String, String> userRequest;
    private String template;

    public Map<String, String> getUserRequest() {
        return userRequest;
    }

    public void setUserRequest(Map<String, String> userRequest) {
        this.userRequest = userRequest;
    }

    public String getTemplate() {
        return template;
    }

    public void setTemplate(String template) {
        this.template = template;
    }
}