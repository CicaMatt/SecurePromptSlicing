import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return renderTemplate("hello.html", username);
        });
    }

    private static String renderTemplate(String templateName, String username) {
        try {
            StringBuilder contentBuilder = new StringBuilder();
            java.nio.file.Files.lines(java.nio.file.Paths.get(templateName))
                    .forEach(contentBuilder::append);
            return contentBuilder.toString().replace("${username}", username);
        } catch (java.io.IOException e) {
            throw new RuntimeException("Error reading template file", e);
        }
    }
}



<!-- hello.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>