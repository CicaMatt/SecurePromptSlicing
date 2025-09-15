import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.Version;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(env);
            }
        });
    }

    private static Configuration env = createFreemarkerConfiguration();

    private static String render_response_from_env(Configuration env, Request request) throws Exception {
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }

        Template template = env.getTemplate("hello.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.getBuffer().toString();
    }

    private static String home(Configuration env) throws Exception {
        Request request = Spark.request();
        return render_response_from_env(env, request);
    }

    private static Configuration createFreemarkerConfiguration() throws Exception {
        Configuration cfg = new Configuration(new Version("2.3.30"));
        cfg.setClassForTemplateLoading(Main.class, "/");
        cfg.setDefaultEncoding("UTF-8");
        return cfg;
    }
}
