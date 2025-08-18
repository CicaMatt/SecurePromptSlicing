import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return renderHelloTemplate(username);
        });
    }

    private static String renderHelloTemplate(String username) {
        StringBuilder templateBuilder = new StringBuilder();
        templateBuilder.append("<html><body>");
        templateBuilder.append("<h1>Hello, ").append(username).append("!</h1>");
        templateBuilder.append("</body></html>");
        return templateBuilder.toString();
    }
}



<!-- hello.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


Note: The HTML part is provided for reference as per your request, but it won't be directly used in the Java code since we are building the response string manually. If you want to use an actual template engine like Thymeleaf or FreeMarker, additional setup would be required.