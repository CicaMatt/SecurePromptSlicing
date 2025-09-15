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

    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");

        Spark.get("/", (request, response) -> home(request, response, cfg));
    }

    public static String renderResponseFromEnv(Request request, Response response, Configuration env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("template.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.getBuffer().toString();
    }

    public static String home(Request request, Response response, Configuration env) throws Exception {
        return renderResponseFromEnv(request, response, env);
    }
}
