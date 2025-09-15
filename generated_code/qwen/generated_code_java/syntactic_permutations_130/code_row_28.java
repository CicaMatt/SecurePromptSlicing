import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Map<String, Object> env) throws Exception {
        Request request = (Request) env.get("request");
        Configuration cfg = (Configuration) env.get("templateEngine").getAttribute("configuration");

        String name = request.queryParams("name");
        Map<String, Object> attributes = new HashMap<>();
        attributes.put("name", name);

        Template template = cfg.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);
        return writer.toString();
    }

    public static String home(Request request, Response response) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine(cfg);

        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("templateEngine", freeMarkerEngine);

        return render_response_from_env(env);
    }
}
