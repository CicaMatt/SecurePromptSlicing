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

    private static Configuration freeMarkerConfig;

    static {
        freeMarkerConfig = new Configuration(Configuration.VERSION_2_3_30);
        freeMarkerConfig.setClassForTemplateLoading(WebApp.class, "/freemarker");
    }

    public static String render_response_from_env(Request request, Response response) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        attributes.put("name", name);

        Template template = freeMarkerConfig.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        template.process(attributes, writer);
        return writer.toString();
    }

    public static String home(Request request, Response response) throws Exception {
        return render_response_from_env(request, response);
    }

    public static void main(String[] args) {
        Spark.get("/", WebApp::home);
    }
}



<!-- Place this file in src/main/resources/freemarker/hello.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>