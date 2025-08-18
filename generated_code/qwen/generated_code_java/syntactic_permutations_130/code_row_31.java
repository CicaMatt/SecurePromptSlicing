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
import freemarker.template.TemplateException;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Configuration env, Request request) {
        try {
            String name = request.queryParams("name");
            Template template = env.getTemplate("hello.ftl");
            Map<String, Object> attributes = new HashMap<>();
            attributes.put("name", name);
            StringWriter writer = new StringWriter();
            template.process(attributes, writer);
            return writer.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static String home(Request request, Response response) {
        Configuration env = new Configuration(Configuration.VERSION_2_3_30);
        env.setClassForTemplateLoading(Main.class, "/templates");
        return render_response_from_env(env, request);
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