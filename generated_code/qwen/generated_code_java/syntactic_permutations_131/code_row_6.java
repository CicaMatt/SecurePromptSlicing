import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static void main(String[] args) {
        Spark.get("/", TemplateRenderer::home);
    }

    private static String renderResponseFromEnv(Request request, Response response, Configuration env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("hello.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    private static String home(Request request, Response response) {
        try {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(TemplateRenderer.class, "/freemarker");
            return renderResponseFromEnv(request, response, cfg);
        } catch (Exception e) {
            e.printStackTrace();
            response.status(500);
            return "Server Error";
        }
    }
}
