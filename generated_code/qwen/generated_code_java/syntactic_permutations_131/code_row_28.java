import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Spark.get("/home", TemplateRenderer::renderResponseFromEnv, new FreeMarkerEngine());
    }

    public static String renderResponseFromEnv(Request request, Response response) {
        Map<String, Object> attributes = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        attributes.put("name", name);
        return new FreeMarkerEngine().render(new spark.ModelAndView(attributes, "home.ftl"));
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>