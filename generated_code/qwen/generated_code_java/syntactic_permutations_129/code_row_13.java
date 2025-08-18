import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res), new FreeMarkerEngine());
    }

    public static String render_response_from_env(Request req, Response res) {
        Map<String, Object> attributes = new HashMap<>();
        String name = req.queryParams("name");
        if (name == null) {
            name = "World";
        }
        attributes.put("name", name);
        return new FreeMarkerEngine().render(new ModelAndView(attributes, "hello.ftl"));
    }

    public static String home(Request req, Response res) {
        return render_response_from_env(req, res);
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello ${name}!</h1>
</body>
</html>