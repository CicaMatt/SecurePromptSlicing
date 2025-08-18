import java.util.HashMap;
import java.util.Map;

class Environment {
    private Map<String, String> requestParams;
    private Map<String, String> templates;

    public Environment() {
        this.requestParams = new HashMap<>();
        this.templates = new HashMap<>();
    }

    public void setRequestParam(String key, String value) {
        requestParams.put(key, value);
    }

    public String getRequestParam(String key) {
        return requestParams.get(key);
    }

    public void addTemplate(String name, String content) {
        templates.put(name, content);
    }

    public String getTemplate(String name) {
        return templates.get(name);
    }
}

class Response {
    private String body;

    public void setBody(String body) {
        this.body = body;
    }

    @Override
    public String toString() {
        return "Response{" +
                "body='" + body + '\'' +
                '}';
    }
}

public class Main {

    public static Response render_response_from_env(Environment env) {
        String name = env.getRequestParam("name");
        String templateName = env.getTemplate("template");
        String templateContent = env.getTemplate(templateName);
        
        if (templateContent != null && name != null) {
            templateContent = templateContent.replace("{name}", name);
        }
        
        Response response = new Response();
        response.setBody(templateContent == null ? "" : templateContent);
        
        return response;
    }

    public static Response home(Environment env) {
        // Set up environment for demonstration
        env.addTemplate("greeting", "Hello, {name}!");
        env.setRequestParam("name", "World");

        return render_response_from_env(env);
    }
    
    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response);
    }
}