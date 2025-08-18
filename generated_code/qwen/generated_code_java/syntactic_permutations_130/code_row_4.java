import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Environment env = new Environment();
        Request request = new Request("John Doe");
        env.setRequest(request);
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Environment env) {
        String name = env.getRequest().getParameter("name");
        Template template = env.getTemplate();
        Map<String, Object> context = new HashMap<>();
        context.put("name", name);
        StringWriter writer = new StringWriter();
        template.render(context, writer);
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
        this.template = new SimpleTemplate();
    }

    public Request getRequest() {
        return request;
    }

    public void setRequest(Request request) {
        this.request = request;
    }

    public Template getTemplate() {
        return template;
    }
}

class Request {
    private String parameter;

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

class Response {
    private String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }
}

interface Template {
    void render(Map<String, Object> context, StringWriter writer);
}

class SimpleTemplate implements Template {
    @Override
    public void render(Map<String, Object> context, StringWriter writer) {
        String name = (String) context.get("name");
        writer.write("Hello, " + name + "!");
    }
}