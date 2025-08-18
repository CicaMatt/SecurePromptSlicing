import io.javalin.Javalin;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            try {
                String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
                String response = renderTemplate(templateContent, username);
                ctx.result(response);
            } catch (Exception e) {
                ctx.status(500).result("Internal Server Error: " + e.getMessage());
            }
        });
    }

    private static String renderTemplate(String template, String username) {
        return template.replace("{username}", username);
    }
}


Make sure you have the `hello.html` file in your project's root directory with content like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {username}!</h1>
</body>
</html>


To run this code, ensure you have Javalin as a dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.12.0</version>
</dependency>


Or include it in your `build.gradle` if you are using Gradle:


implementation 'io.javalin:javalin:4.12.0'