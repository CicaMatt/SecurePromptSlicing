import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static void main(String[] args) {
        try {
            // Initialize the FreeMarker configuration
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(TemplateRenderer.class, "/");

            // Create an environment map to simulate request parameters and template
            Map<String, Object> env = new HashMap<>();
            env.put("name", "World");
            env.put("templateName", "hello.ftl");

            // Call the home function to render the response
            String response = home(env);
            System.out.println(response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String render_response_from_env(Map<String, Object> env) throws Exception {
        Configuration cfg = (Configuration) env.getOrDefault("cfg", new Configuration(Configuration.VERSION_2_3_31));
        cfg.setClassForTemplateLoading(TemplateRenderer.class, "/");

        // Get the name parameter from the request
        String name = (String) env.get("name");

        // Get the template from the environment
        Template template = cfg.getTemplate((String) env.get("templateName"));

        // Create a data model to hold the parameters for rendering
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        // Render the template with the name parameter
        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        // Return the rendered template
        return out.getBuffer().toString();
    }

    public static String home(Map<String, Object> env) throws Exception {
        // Call the render_response_from_env function with the env variable
        return render_response_from_env(env);
    }
}
