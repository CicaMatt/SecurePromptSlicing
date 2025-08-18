import com.google.gson.Gson;
import spark.Filter;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.port(4567);

        // Decorator to bind function to URL
        Spark.before("/hello/*", new Filter() {
            @Override
            public void handle(Request req, Response res) throws Exception {
                String path = req.pathInfo();
                if (path.startsWith("/hello/")) {
                    String username = path.substring(7);
                    Map<String, Object> templateData = new HashMap<>();
                    templateData.put("username", username);

                    try {
                        String htmlTemplate = new String(Files.readAllBytes(Paths.get("hello.html")));
                        String renderedHtml = renderTemplate(htmlTemplate, templateData);
                        res.type("text/html");
                        res.body(renderedHtml);
                    } catch (IOException e) {
                        res.status(500);
                        res.body("Internal Server Error");
                    }
                }
            }
        });
    }

    private static String renderTemplate(String template, Map<String, Object> data) {
        Gson gson = new Gson();
        return template.replace("${username}", gson.toJson(data.get("username")));
    }
}


**hello.html:**


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


Ensure you have the `hello.html` file in the same directory as your Java code and include Spark framework dependencies in your project.