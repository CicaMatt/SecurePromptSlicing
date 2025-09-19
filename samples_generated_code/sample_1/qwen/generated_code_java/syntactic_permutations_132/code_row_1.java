import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request req, Response res) -> {
            String username = req.params(":username");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            return new ThymeleafTemplateEngine().render(new spark.ModelAndView(model, "hello"));
        });
    }
}

<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Hello Page</title>
</head>
<body>
<h1 th:text="'Hello, ' + ${username} + '!'"></h1>
</body>
</html>