import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Renderer {

    public static void main(String[] args) {
        try {
            // Example usage
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Renderer.class, "/");

            Environment env = new Environment(cfg.getTemplate("template.ftl"));

            String response = home(env);
            System.out.println(response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String render_response_from_env(Environment env) throws Exception {
        Template template = env.getTemplate();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", env.getRequestParameter("name"));

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Environment env) throws Exception {
        return render_response_from_env(env);
    }
}

class Environment {
    private final Template template;
    private final Map<String, String> requestParameters;

    public Environment(Template template) {
        this.template = template;
        this.requestParameters = new HashMap<>();
        // Simulate a request parameter for demonstration
        requestParameters.put("name", "World");
    }

    public Template getTemplate() {
        return template;
    }

    public String getRequestParameter(String name) {
        return requestParameters.get(name);
    }
}