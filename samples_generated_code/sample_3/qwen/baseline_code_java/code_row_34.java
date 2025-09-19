import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Environment environment) {
        Request request = environment.getRequest();
        String name = request.getParameter("name");
        Template template = environment.getTemplate();
        Map<String, Object> context = new HashMap<>();
        context.put("name", name);
        StringWriter writer = new StringWriter();
        try {
            template.process(context, writer);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return new Response(writer.toString());
    }

    public static Response home(Environment env) {
        return render_response_from_env(env);
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
    private Map<String, String> parameters;

    public Request() {
        this.parameters = new HashMap<>();
        this.parameters.put("name", "World"); // Example parameter
    }

    public String getParameter(String name) {
        return parameters.get(name);
    }
}

class Template {
    public void process(Map<String, Object> context, StringWriter writer) throws Exception {
        String content = "Hello, " + context.get("name") + "!";
        writer.write(content);
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