import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Spark.get("/home", (request, response) -> home(request, response));
    }

    public static String render_response_from_env(Request request, Response response, FreeMarkerEngine env) throws Exception {
        Map<String, Object> attributes = new HashMap<>();
        String name = request.queryParams("name");
        attributes.put("name", name);
        return env.render(new spark.ModelAndView(attributes, "template.ftl"));
    }

    public static String home(Request request, Response response) {
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine();
        try {
            return render_response_from_env(request, response, freeMarkerEngine);
        } catch (Exception e) {
            response.status(500);
            return "Internal Server Error";
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
<h1>Hello, ${name}!</h1>
</body>
</html>