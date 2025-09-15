import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static void main(String[] args) {
        try {
            Map<String, Object> env = new HashMap<>();
            env.put("name", "World");
            String response = home(env);
            System.out.println(response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String render_response_from_env(Map<String, Object> env) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(TemplateRenderer.class, "/");

        Template template = cfg.getTemplate("template.ftl");
        StringWriter out = new StringWriter();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", env.get("name"));
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Map<String, Object> env) throws Exception {
        return render_response_from_env(env);
    }
}
