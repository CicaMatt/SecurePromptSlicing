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
        Map<String, Object> dataModel = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }
        dataModel.put("name", name);

        Template template = env.getTemplate("hello.ftl");

        StringWriter stringWriter = new StringWriter();
        template.process(dataModel, stringWriter);
        return stringWriter.toString();
    }

    public static String home(Request request, Response response) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");
        return render_response_from_env(cfg, request);
    }
}
