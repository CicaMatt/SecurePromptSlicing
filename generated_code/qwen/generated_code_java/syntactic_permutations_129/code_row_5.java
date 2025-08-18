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
                Map<String, Object> env = new HashMap<>();
                env.put("request", request);
                env.put("configuration", createFreemarkerConfiguration());
                return home(env);
            }
        });
    }

    private static String home(Map<String, Object> env) throws Exception {
        Request request = (Request) env.get("request");
        Configuration cfg = (Configuration) env.get("configuration");

        return renderResponseFromEnv(request, cfg);
    }

    private static String renderResponseFromEnv(Request request, Configuration cfg) throws Exception {
        String name = request.queryParams("name");
        Template template = cfg.getTemplate("template.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        return out.toString();
    }

    private static Configuration createFreemarkerConfiguration() throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");
        cfg.setDefaultEncoding("UTF-8");

        return cfg;
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Greeting</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>