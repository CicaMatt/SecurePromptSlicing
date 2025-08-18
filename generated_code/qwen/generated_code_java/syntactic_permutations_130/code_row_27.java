import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Map<String, Object> environment) {
        Configuration cfg = (Configuration) environment.get("template_engine");
        Template template = (Template) environment.get("template");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", request.queryParams("name"));

        StringWriter out = new StringWriter();
        try {
            template.process(dataModel, out);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        return out.toString();
    }

    public static String home(Request request, Response response) {
        Map<String, Object> environment = new HashMap<>();
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);

        try {
            cfg.setClassForTemplateLoading(Main.class, "/templates");
            Template template = cfg.getTemplate("home.ftl");

            environment.put("template_engine", cfg);
            environment.put("template", template);

            return render_response_from_env(environment);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}



<!-- /templates/home.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Welcome</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>