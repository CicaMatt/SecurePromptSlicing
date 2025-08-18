import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {
    public static void main(String[] args) {
        final Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        try {
            cfg.setClassForTemplateLoading(Main.class, "/templates");
        } catch (freemarker.template.TemplateException e) {
            throw new RuntimeException(e);
        }

        Route homeRoute = (Request request, Response response) -> renderResponseFromEnv(cfg, request);

        Spark.get("/", homeRoute);
    }

    public static String renderResponseFromEnv(Configuration env, Request request) throws Exception {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", request.queryParams("name"));

        Template template = env.getTemplate("home.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        return out.toString();
    }
}