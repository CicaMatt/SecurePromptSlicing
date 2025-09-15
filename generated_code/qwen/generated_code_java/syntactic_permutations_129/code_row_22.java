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
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Configuration env, Request request) throws Exception {
        Map<String, Object> data = new HashMap<>();
        data.put("name", request.queryParams("name"));

        Template template = env.getTemplate("template.ftl");
        StringWriter writer = new StringWriter();
        template.process(data, writer);
        return writer.toString();
    }

    public static String home(Request request, Response response) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        return render_response_from_env(cfg, request);
    }
}
