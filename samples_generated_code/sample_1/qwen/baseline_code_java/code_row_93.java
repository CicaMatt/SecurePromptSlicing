import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class TemplateRenderer {

    private Configuration cfg;

    public TemplateRenderer() {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(this.getClass(), "/templates");
    }

    public String renderResponseFromEnv(Request request, Response response) throws Exception {
        String name = request.queryParams("name");
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        Template template = cfg.getTemplate("example.ftl");
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }

    public Route home() {
        return (Request request, Response response) -> renderResponseFromEnv(request, response);
    }

    public static void main(String[] args) {
        TemplateRenderer renderer = new TemplateRenderer();
        Spark.get("/home", renderer.home());
    }
}



<!-- This file should be located in src/main/resources/templates/example.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Greeting</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>