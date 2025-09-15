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
        cfg.setClassForTemplateLoading(Main.class, "/");

        Route homeRoute = (Request request, Response response) -> {
            return renderResponseFromEnv(cfg, request);
        };

        Spark.get("/", homeRoute);
    }

    public static String renderResponseFromEnv(Configuration env, Request request) throws Exception {
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }
        Template template = env.getTemplate("hello.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }
}
