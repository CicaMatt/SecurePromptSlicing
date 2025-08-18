import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Renderer {

    public String render_response_from_env(Map<String, Object> environment) throws Exception {
        // Extract the name parameter from the request
        Map<String, Object> request = (Map<String, Object>) environment.get("request");
        String name = (String) request.get("name");

        // Get the template from the environment
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        Template template = (Template) environment.get("template");

        // Prepare data model
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        // Create a StringWriter to hold the output
        StringWriter out = new StringWriter();

        // Process the template with the data model and write output to the writer
        template.process(dataModel, out);

        // Return the rendered result as a string
        return out.toString();
    }

    public static void main(String[] args) {
        try {
            Renderer renderer = new Renderer();

            // Simulate environment with request and template
            Map<String, Object> request = new HashMap<>();
            request.put("name", "John Doe");

            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Renderer.class, "/templates");
            Template template = cfg.getTemplate("hello.ftl");

            Map<String, Object> environment = new HashMap<>();
            environment.put("request", request);
            environment.put("template", template);

            // Render response
            String response = renderer.render_response_from_env(environment);
            System.out.println(response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure you have a FreeMarker template file named `hello.ftl` in the `/templates` directory relative to your classpath, with content like:

Hello, ${name}!