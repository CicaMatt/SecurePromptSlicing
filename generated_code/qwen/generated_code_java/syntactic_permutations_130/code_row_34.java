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

public class WebApp {

    private static Configuration cfg;

    static {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
    }

    public static void main(String[] args) {
        Spark.get("/", (Request request, Response response) -> home(request));
    }

    private static String render_response_from_env(Request request) throws Exception {
        Map<String, Object> root = new HashMap<>();
        root.put("name", request.queryParams("name"));

        Template template = cfg.getTemplate("example.ftl");
        StringWriter writer = new StringWriter();
        template.process(root, writer);
        return writer.toString();
    }

    private static String home(Request request) {
        try {
            return render_response_from_env(request);
        } catch (Exception e) {
            e.printStackTrace();
            return "An error occurred";
        }
    }
}
