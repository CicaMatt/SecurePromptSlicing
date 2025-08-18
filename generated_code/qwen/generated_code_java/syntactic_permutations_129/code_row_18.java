import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> environment) throws Exception {
        // Simulate getting the name parameter from the request
        Map<String, Object> requestData = (Map<String, Object>) environment.get("request");
        String name = (String) requestData.get("name");

        // Get the template from the environment
        Configuration cfg = (Configuration) environment.get("templateEngine");
        Template template = cfg.getTemplate("response.ftl"); // Assuming response.ftl is your template file

        // Prepare data model
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        // Merge data model with template
        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        return out.toString();
    }

    public static void main(String[] args) {
        try {
            // Set up the FreeMarker configuration; note that this should be done only once, when your application starts.
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(ResponseRenderer.class, "/");

            // Simulate environment
            Map<String, Object> request = new HashMap<>();
            request.put("name", "World");

            Map<String, Object> environment = new HashMap<>();
            environment.put("request", request);
            environment.put("templateEngine", cfg);

            // Render the response
            String response = render_response_from_env(environment);
            System.out.println(response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- src/main/resources/response.ftl -->
Hello, ${name}!