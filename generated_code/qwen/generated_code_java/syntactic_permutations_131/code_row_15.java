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
    private static Configuration cfg;

    public static void main(String[] args) {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/");

        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                Map<String, Object> env = new HashMap<>();
                env.put("request", request);
                return home(env);
            }
        });
    }

    private static String render_response_from_env(Map<String, Object> env) throws Exception {
        Request request = (Request) env.get("request");
        String name = request.queryParams("name");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        Template template = cfg.getTemplate("template.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    private static String home(Map<String, Object> env) throws Exception {
        return render_response_from_env(env);
    }
}
