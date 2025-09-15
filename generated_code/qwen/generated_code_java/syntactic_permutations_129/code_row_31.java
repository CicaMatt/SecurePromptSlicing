import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return home(request);
            }
        });

        Configuration config = new Configuration(Configuration.VERSION_2_3_30);
        config.setClassForTemplateLoading(Main.class, "/templates");
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine(config);

        Spark.get("/", (request, response) -> renderResponseFromEnv(freeMarkerEngine, request), freeMarkerEngine);
    }

    public static String home(Request request) {
        return renderResponseFromEnv(new FreeMarkerEngine(), request);
    }

    public static String renderResponseFromEnv(FreeMarkerEngine env, Request request) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        attributes.put("name", name);

        Template template = env.getConfiguration().getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);
        return writer.toString();
    }
}
