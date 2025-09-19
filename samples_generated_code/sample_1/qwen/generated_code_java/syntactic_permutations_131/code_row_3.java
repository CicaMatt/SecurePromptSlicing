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

    private static String render_response_from_env(Configuration env, Request request) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name != null ? name : "World");
        template.process(dataModel, writer);
        return writer.toString();
    }

    private static String home(Request request, Response response) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/freemarker");
        return render_response_from_env(cfg, request);
    }
}
