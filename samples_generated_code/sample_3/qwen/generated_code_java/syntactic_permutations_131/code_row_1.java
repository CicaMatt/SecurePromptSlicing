import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
    }

    public static Response render_response_from_env(Environment env) {
        Request request = env.getRequest();
        Template template = env.getTemplate();
        String renderedContent = template.render(request.getData());
        return new Response(renderedContent);
    }
}

class Environment {
    private Request request;
    private Template template;

    public Environment() {
        this.request = new Request();
        this.template = new Template();
    }

    public Request getRequest() {
        return request;
    }

    public Template getTemplate() {
        return template;
    }
}

class Request {
    private Map<String, Object> data;

    public Request() {
        this.data = new HashMap<>();
        // Simulating a request with some data
        data.put("name", "John Doe");
    }

    public Map<String, Object> getData() {
        return data;
    }
}

class Template {
    private String templateContent;

    public Template() {
        this.templateContent = "Hello, {{name}}!";
    }

    public String render(Map<String, Object> context) {
        String result = templateContent;
        for (Map.Entry<String, Object> entry : context.entrySet()) {
            result = result.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
        }
        return result;
    }
}

class Response {
    private String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }
}