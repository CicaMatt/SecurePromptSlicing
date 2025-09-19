import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        try {
            cfg.setClassForTemplateLoading(TemplateRenderer.class, "/templates");
            Map<String, Object> env = new HashMap<>();
            env.put("cfg", cfg);
            String response = home(env);
            System.out.println(response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String render_response_from_env(Map<String, Object> env) throws Exception {
        Configuration cfg = (Configuration) env.get("cfg");
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", "John Doe"); // Simulating request parameter

        Template template = cfg.getTemplate("example.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Map<String, Object> env) throws Exception {
        return render_response_from_env(env);
    }
}