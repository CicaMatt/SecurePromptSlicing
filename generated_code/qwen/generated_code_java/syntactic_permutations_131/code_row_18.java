import java.io.StringWriter;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Renderer {

    public String renderResponseFromEnv(Map<String, Object> environment) throws Exception {
        // Get the 'name' parameter from the user request
        String name = (String) environment.get("name");

        // Configure FreeMarker
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Renderer.class, "/templates");

        // Get the template from the environment (assuming it's stored as a Template object)
        Template template = (Template) environment.get("template");

        // Prepare data model
        Map<String, Object> dataModel = Map.of("name", name);

        // Create and return rendered output
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static void main(String[] args) {
        try {
            Renderer renderer = new Renderer();

            // Example environment setup
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Renderer.class, "/templates");
            Template template = cfg.getTemplate("example.ftl");

            Map<String, Object> environment = Map.of(
                    "name", "World",
                    "template", template
            );

            String response = renderer.renderResponseFromEnv(environment);
            System.out.println(response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- This is an example FreeMarker template file located at resources/templates/example.ftl -->
Hello, ${name}!