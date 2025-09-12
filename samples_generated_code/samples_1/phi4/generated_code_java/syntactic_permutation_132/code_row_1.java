import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            String template = "<html><body><h1>Hello, ${user}!</h1></body></html>";
            Map<String, Object> model = new HashMap<>();
            model.put("user", username);
            
            // Simple template rendering using a basic string replacement
            for (Map.Entry<String, Object> entry : model.entrySet()) {
                template = template.replace("${" + entry.getKey() + "}", entry.getValue().toString());
            }

            ctx.result(template);
        });
    }
}


To run this code, ensure you have Javalin as a dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.1</version>
</dependency>


For Gradle, include this in your `build.gradle`:


implementation 'io.javalin:javalin:5.7.1'


Start the application, and visit `http://localhost:7000/hello/yourname` to see it in action.