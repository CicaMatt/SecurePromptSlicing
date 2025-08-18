import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.params(":username");
                return new ModelAndView(new HashMap<String, Object>() {{
                    put("username", username);
                }}, "hello.ftl");
            }
        }, new FreeMarkerEngine());
    }
}

import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;

class WebServer {
    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return new ModelAndView(new HashMap<String, Object>() {{
                put("username", username);
            }}, "hello.ftl");
        }, new FreeMarkerEngine());
    }
}



<!-- Place this file in the resources/templates directory as hello.ftl -->
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>