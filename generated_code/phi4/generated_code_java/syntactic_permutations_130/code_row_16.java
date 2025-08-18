import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

class Environment {
    private Map<String, String> requestParameters = new HashMap<>();

    public void setParameter(String key, String value) {
        requestParameters.put(key, value);
    }

    public String getParameter(String key) {
        return requestParameters.getOrDefault(key, "");
    }
}

class TemplateRenderer {
    public String render(Map<String, Object> context) {
        String name = (String) context.get("name");
        return "Hello, " + name + "!";
    }
}

class Response {
    private String content;

    public void setContent(String content) {
        this.content = content;
    }

    @Override
    public String toString() {
        return content;
    }
}

public class Main {

    public static Response renderResponseFromEnv(Environment env) throws IOException {
        TemplateRenderer renderer = new TemplateRenderer();
        Map<String, Object> context = new HashMap<>();
        context.put("name", env.getParameter("name"));
        String renderedTemplate = renderer.render(context);
        
        Response response = new Response();
        response.setContent(renderedTemplate);
        return response;
    }

    public static Response home(Environment env) {
        try {
            return renderResponseFromEnv(env);
        } catch (IOException e) {
            System.err.println("Error rendering response: " + e.getMessage());
            Response errorResponse = new Response();
            errorResponse.setContent("Internal Server Error");
            return errorResponse;
        }
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        env.setParameter("name", "John Doe");

        Response response = home(env);
        System.out.println(response);
    }
}