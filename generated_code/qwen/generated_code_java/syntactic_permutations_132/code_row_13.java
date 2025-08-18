import spark.Request;
import spark.Response;
import spark.Spark;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class HelloServer {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        try {
            cfg.setClassForTemplateLoading(HelloServer.class, "/templates");
            Spark.get("/hello/:username", (Request req, Response res) -> {
                String username = req.params(":username");
                Map<String, Object> model = new HashMap<>();
                model.put("username", username);
                Template template = cfg.getTemplate("hello.html");
                StringWriter writer = new StringWriter();
                template.process(model, writer);
                return writer.toString();
            });
        } catch (Exception e) {
            Spark.halt(500);
        }
    }
}



<!-- This file should be located in src/main/resources/templates/hello.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>