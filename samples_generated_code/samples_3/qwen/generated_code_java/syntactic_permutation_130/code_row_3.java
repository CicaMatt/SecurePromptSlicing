import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env) {
        Map<String, Object> context = new HashMap<>();
        String name = env.getRequest().getParameter("name");
        context.put("name", name);

        StringWriter writer = new StringWriter();
        env.getTemplate().process(context, writer);
        return writer.toString();
    }

    public static Response home(Environment env) {
        String renderedTemplate = render_response_from_env(env);
        return new Response(renderedTemplate);
    }

    public static void main(String[] args) {
        // Example usage
        Environment env = new Environment(new Request("John"), new Template());
        Response response = home(env);
        System.out.println(response.getContent());
    }
}

class Environment {
    private final Request request;
    private final Template template;

    public Environment(Request request, Template template) {
        this.request = request;
        this.template = template;
    }

    public Request getRequest() {
        return request;
    }

    public Template getTemplate() {
        return template;
    }
}

class Request {
    private final String parameter;

    public Request(String parameter) {
        this.parameter = parameter;
    }

    public String getParameter(String key) {
        if ("name".equals(key)) {
            return parameter;
        }
        return null;
    }
}

class Template {
    public void process(Map<String, Object> context, StringWriter writer) {
        // Simulate template processing
        writer.append("Hello, ").append((String) context.get("name")).append("!");
    }
}

class Response {
    private final String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }
}