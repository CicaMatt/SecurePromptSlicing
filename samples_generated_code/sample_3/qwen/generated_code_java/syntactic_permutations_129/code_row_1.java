import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import spark.Request;
import spark.Response;
import spark.Spark;

public class TemplateRenderer {

    private static Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);

    public static void main(String[] args) {
        Spark.get("/", TemplateRenderer::home);
    }

    public static String home(Request req, Response res) throws Exception {
        Map<String, Object> env = new HashMap<>();
        return renderResponseFromEnv(req, env);
    }

    public static String renderResponseFromEnv(Request req, Map<String, Object> env) throws Exception {
        cfg.setClassForTemplateLoading(TemplateRenderer.class, "/templates");
        Template template = cfg.getTemplate("template.ftl");

        String name = req.queryParams("name");
        if (name != null) {
            env.put("name", name);
        }

        StringWriter writer = new StringWriter();
        template.process(env, writer);

        return writer.toString();
    }
}