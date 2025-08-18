import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public String render_response_from_env(Configuration env, Map<String, String> requestParameters) throws Exception {
        String name = requestParameters.get("name");
        
        if (env == null || name == null) {
            throw new IllegalArgumentException("Environment and 'name' parameter must not be null.");
        }

        Template template = env.getTemplate("template.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        return out.toString();
    }

    public static void main(String[] args) {
        try {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(TemplateRenderer.class, "/");

            Map<String, String> requestParameters = new HashMap<>();
            requestParameters.put("name", "John Doe");

            TemplateRenderer renderer = new TemplateRenderer();
            String result = renderer.render_response_from_env(cfg, requestParameters);
            System.out.println(result);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- src/main/resources/template.ftl -->
Hello, ${name}!