import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    private static String render_response_from_env(Configuration env, Request request) throws Exception {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", request.queryParams("name"));

        Template template = env.getTemplate("home.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    private static String home(Request request, Response response) {
        try {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Main.class, "/templates");
            return render_response_from_env(cfg, request);
        } catch (Exception e) {
            response.status(500);
            return "Server Error";
        }
    }
}