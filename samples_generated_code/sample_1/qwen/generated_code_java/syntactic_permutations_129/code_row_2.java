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

    public static String render_response_from_env(Request req, Response res, ThymeleafTemplateEngine env) {
        Map<String, Object> model = new HashMap<>();
        String name = req.queryParams("name");
        if (name == null) {
            name = "World";
        }
        model.put("name", name);
        return env.render(new ModelAndView(model, "template.html"));
    }

    public static String home(Request req, Response res) {
        ThymeleafTemplateEngine engine = new ThymeleafTemplateEngine();
        return render_response_from_env(req, res, engine);
    }
}



<!-- src/main/resources/templates/template.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Greeting</title>
</head>
<body>
    <h1>Hello, <span th:text="${name}">Name</span>!</h1>
</body>
</html>