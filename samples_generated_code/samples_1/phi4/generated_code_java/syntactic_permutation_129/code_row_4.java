import java.util.Map;

interface TemplateEngine {
    String render(String template, Map<String, Object> context);
}

class Environment {
    private final Map<String, Object> data;
    private final TemplateEngine templateEngine;

    public Environment(Map<String, Object> data, TemplateEngine templateEngine) {
        this.data = data;
        this.templateEngine = templateEngine;
    }

    public String getTemplate() {
        return (String) data.get("template");
    }

    public Map<String, Object> getData() {
        return data;
    }

    public TemplateEngine getTemplateEngine() {
        return templateEngine;
    }
}

class SimpleTemplateEngine implements TemplateEngine {
    @Override
    public String render(String template, Map<String, Object> context) {
        StringBuilder result = new StringBuilder(template);
        for (Map.Entry<String, Object> entry : context.entrySet()) {
            String placeholder = "{{" + entry.getKey() + "}}";
            result = new StringBuilder(result.toString().replace(placeholder, entry.getValue().toString()));
        }
        return result.toString();
    }
}

public class Main {

    public static String renderResponseFromEnv(Environment env) {
        String name = (String) env.getData().get("name");
        String template = env.getTemplate();
        Map<String, Object> context = Map.of("name", name);
        TemplateEngine engine = env.getTemplateEngine();
        
        return engine.render(template, context);
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        // Sample data
        Map<String, Object> data = Map.of("name", "World", "template", "<h1>Hello, {{name}}!</h1>");
        
        TemplateEngine engine = new SimpleTemplateEngine();
        Environment env = new Environment(data, engine);

        String response = home(env);
        System.out.println(response); // Outputs: <h1>Hello, World!</h1>
    }
}