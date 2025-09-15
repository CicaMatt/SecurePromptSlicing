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
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request);
            }
        });
    }

    public static String home(Request request) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        return render_response_from_env(env);
    }

    public static String render_response_from_env(Map<String, Object> env) throws Exception {
        Request request = (Request) env.get("request");
        String name = request.queryParams("name");

        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");

        Template template = cfg.getTemplate("hello.ftl");
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        return out.toString();
    }
}
