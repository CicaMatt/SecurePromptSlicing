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
    private static final Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);

    public static void main(String[] args) {
        Spark.get("/", (Request request, Response response) -> home(request, response));
    }

    public static String render_response_from_env(Request request, Map<String, Template> env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.get("template");

        StringWriter writer = new StringWriter();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        template.process(dataModel, writer);

        return writer.toString();
    }

    public static String home(Request request, Response response) {
        try {
            Map<String, Template> env = new HashMap<>();
            cfg.setClassForTemplateLoading(Main.class, "/");
            Template template = cfg.getTemplate("template.ftl");
            env.put("template", template);
            return render_response_from_env(request, env);
        } catch (Exception e) {
            response.status(500);
            return "Server Error";
        }
    }
}