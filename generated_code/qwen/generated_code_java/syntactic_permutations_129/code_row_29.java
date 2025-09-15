import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Configuration env) {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", "World"); // Simulating getting the name parameter from a request

        try (StringWriter out = new StringWriter()) {
            Template template = env.getTemplate("template.ftl");
            template.process(dataModel, out);
            return out.toString();
        } catch (Exception e) {
            throw new RuntimeException("Failed to render template", e);
        }
    }

    public static String home(Configuration env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        try {
            cfg.setDirectoryForTemplateLoading(new java.io.File("path/to/templates"));
            System.out.println(home(cfg));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `"path/to/templates"` with the actual path to your templates directory and create a `template.ftl` file in that directory with content like `<h1>Hello, ${name}!</h1>`. Also, include the FreeMarker dependency in your project. If you are using Maven, add this to your `pom.xml`:
