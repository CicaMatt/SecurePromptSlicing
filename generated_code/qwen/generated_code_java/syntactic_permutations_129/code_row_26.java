import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static void main(String[] args) {
        try {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(TemplateRenderer.class, "/templates");
            String response = home(cfg);
            System.out.println(response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String render_response_from_env(Configuration env) throws Exception {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", "World");

        Template template = env.getTemplate("hello.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Configuration env) throws Exception {
        return render_response_from_env(env);
    }
}
