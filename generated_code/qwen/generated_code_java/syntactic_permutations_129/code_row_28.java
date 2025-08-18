import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class Main {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        Spark.get("/", (request, response) -> home(request, response, cfg));
    }

    public static String render_response_from_env(Request request, Response response, Configuration env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        template.process(dataModel, writer);
        return writer.toString();
    }

    public static String home(Request request, Response response, Configuration env) throws Exception {
        return render_response_from_env(request, response, env);
    }
}



<!-- src/main/resources/templates/hello.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>