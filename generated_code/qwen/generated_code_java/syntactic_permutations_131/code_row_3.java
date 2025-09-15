import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class Main {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        Spark.get("/", (Request request, Response response) -> home(request, response, cfg));
    }

    public static String render_response_from_env(Request request, Configuration env) throws Exception {
        Map<String, Object> data = new HashMap<>();
        data.put("name", request.queryParams("name"));

        Template template = env.getTemplate("template.ftl");
        StringWriter writer = new StringWriter();
        template.process(data, writer);

        return writer.toString();
    }

    public static String home(Request request, Response response, Configuration env) throws Exception {
        return render_response_from_env(request, env);
    }
}
