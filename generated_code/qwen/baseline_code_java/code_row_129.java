import spark.Request;
import spark.Response;
import spark.Spark;
import spark.ModelAndView;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res));
    }

    public static String home(Request req, Response res) {
        ThymeleafTemplateEngine engine = new ThymeleafTemplateEngine();
        return renderResponseFromEnv(engine, req);
    }

    public static String renderResponseFromEnv(ThymeleafTemplateEngine env, Request req) {
        Map<String, Object> model = new HashMap<>();
        String name = req.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        model.put("name", name);
        return env.render(new ModelAndView(model, "index"));
    }
}


<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Greeting</title>
</head>
<body>
<h1>Hello, <span th:text="${name}">World</span>!</h1>
</body>
</html>

<!-- Place the above HTML in src/main/resources/templates/index.html -->