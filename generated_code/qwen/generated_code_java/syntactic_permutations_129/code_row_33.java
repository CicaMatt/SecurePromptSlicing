import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    private static Configuration setupFreemarkerConfig() throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
        return cfg;
    }

    public static String render_response_from_env(Request request, Response response, Configuration env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("hello.ftl");
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name != null ? name : "World");

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public static String home(Request request, Response response) {
        try {
            Configuration env = setupFreemarkerConfig();
            return render_response_from_env(request, response, env);
        } catch (Exception e) {
            response.status(500);
            return "Server Error";
        }
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