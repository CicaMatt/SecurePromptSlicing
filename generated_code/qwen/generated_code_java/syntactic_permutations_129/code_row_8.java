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
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Configuration env, Request request) throws Exception {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", request.queryParams("name"));

        Template template = env.getTemplate("hello.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Request request, Response response) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
        return render_response_from_env(cfg, request);
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>