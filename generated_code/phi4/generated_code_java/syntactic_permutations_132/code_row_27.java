import com.google.gson.Gson;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return renderTemplate(username);
        });
    }

    private static String renderTemplate(String username) {
        try {
            String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("username", username);

            return templateContent
                    .replace("{{username}}", username); // Simple string replacement for demonstration.
        } catch (IOException e) {
            e.printStackTrace();
            return "Error loading template";
        }
    }
}


Make sure you have a `hello.html` file in the same directory with content like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{username}}!</h1>
</body>
</html>


Additionally, add the following dependency to your `pom.xml` for Spark framework:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>