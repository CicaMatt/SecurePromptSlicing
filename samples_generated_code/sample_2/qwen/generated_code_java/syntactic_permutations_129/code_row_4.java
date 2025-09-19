import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.Context;

public class Main {
    public static void main(String[] args) {
        Spark.get("/home", (req, res) -> home(req, res));
    }

    public static String render_response_from_env(Request req, Response res) {
        String name = req.queryParams("name");
        Map<String, Object> model = new HashMap<>();
        model.put("name", name);
        
        TemplateEngine engine = new ThymeleafTemplateEngine();
        StringWriter stringWriter = new StringWriter();
        Context context = new Context();
        context.setVariables(model);

        engine.process("template.html", context, stringWriter);
        return stringWriter.toString();
    }

    public static String home(Request req, Response res) {
        return render_response_from_env(req, res);
    }
}



<!-- src/main/resources/templates/template.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Home</title>
</head>
<body>
    <h1>Hello, <span th:text="${name}">World</span>!</h1>
</body>
</html>