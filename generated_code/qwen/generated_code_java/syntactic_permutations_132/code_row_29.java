import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate("hello.html", "username", username);
            }
        });
    }

    private static String renderTemplate(String templateName, String variableName, String variableValue) {
        try {
            StringBuilder templateBuilder = new StringBuilder();
            java.nio.file.Files.readAllLines(java.nio.file.Paths.get(templateName))
                    .forEach(line -> templateBuilder.append(line).append("\n"));
            String templateContent = templateBuilder.toString();
            return templateContent.replace("{{" + variableName + "}}", variableValue);
        } catch (Exception e) {
            e.printStackTrace();
            return "<h1>Error rendering template</h1>";
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
    <h1>Hello, {{username}}!</h1>
</body>
</html>