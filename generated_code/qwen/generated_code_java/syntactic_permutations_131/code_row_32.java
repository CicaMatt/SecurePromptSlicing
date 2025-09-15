import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.Version;

public class Main {

    public static void main(String[] args) {
        Configuration cfg = new Configuration(new Version("2.3.31"));
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine(cfg);

        Spark.get("/", (request, response) -> home(request, response, freeMarkerEngine));
    }

    public static String render_response_from_env(Request request, Response response, FreeMarkerEngine engine) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        attributes.put("name", request.queryParams("name"));

        Template template = engine.getConfiguration().getTemplate("template.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);

        return writer.toString();
    }

    public static String home(Request request, Response response, FreeMarkerEngine engine) throws Exception {
        return render_response_from_env(request, response, engine);
    }
}
