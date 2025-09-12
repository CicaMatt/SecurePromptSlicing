import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env) {
        Map<String, Object> dataModel = new HashMap<>();
        String nameParameter = env.getRequest().getParameter("name");
        dataModel.put("name", nameParameter);

        StringWriter stringWriter = new StringWriter();
        env.getTemplate().process(dataModel, stringWriter);
        return stringWriter.toString();
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        // Example usage
        Environment env = new Environment(new Request("John Doe"), new Template());
        String response = home(env);
        System.out.println(response);
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
    private final String name;

    public Request(String name) {
        this.name = name;
    }

    public String getParameter(String paramName) {
        if ("name".equals(paramName)) {
            return name;
        }
        return null;
    }
}

class Template {
    public void process(Map<String, Object> dataModel, StringWriter writer) {
        // Simulate template processing
        String name = (String) dataModel.get("name");
        writer.write(String.format("<html><body>Hello, %s!</body></html>", name));
    }
}