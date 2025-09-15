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
                return home(request);
            }
        });
    }

    private static String render_response_from_env(Request request, Configuration env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        template.process(dataModel, writer);
        return writer.toString();
    }

    private static String home(Request request) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/freemarker");
        return render_response_from_env(request, cfg);
    }
}
