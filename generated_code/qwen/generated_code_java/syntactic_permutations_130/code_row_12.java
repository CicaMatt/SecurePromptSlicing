import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env) {
        Map<String, Object> parameters = new HashMap<>();
        parameters.put("name", env.getParameter("name"));
        return env.getTemplate().render(parameters);
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }
}

class Environment {
    private final Map<String, String> params;
    private final Template template;

    public Environment(Map<String, String> params, Template template) {
        this.params = params;
        this.template = template;
    }

    public String getParameter(String key) {
        return params.get(key);
    }

    public Template getTemplate() {
        return template;
    }
}

class Template {
    private final String content;

    public Template(String content) {
        this.content = content;
    }

    public String render(Map<String, Object> parameters) {
        StringBuilder renderedContent = new StringBuilder(content);
        for (Map.Entry<String, Object> entry : parameters.entrySet()) {
            String key = "{{" + entry.getKey() + "}}";
            while (renderedContent.indexOf(key) != -1) {
                int index = renderedContent.indexOf(key);
                renderedContent.replace(index, index + key.length(), entry.getValue().toString());
            }
        }
        return renderedContent.toString();
    }

    public static void main(String[] args) {
        Map<String, String> params = new HashMap<>();
        params.put("name", "World");

        Template template = new Template("Hello, {{name}}!");

        Environment env = new Environment(params, template);

        System.out.println(home(env));
    }
}