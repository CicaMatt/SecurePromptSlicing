import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApplication {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/checkName", Context::handleCheckName);
    }

    private static void handleCheckName(Context ctx) {
        String name = ctx.formParam("name");
        
        if (name != null && !name.isEmpty()) {
            ctx.json(Map.of("name", name));
        } else {
            ctx.status(400).json(Map.of("error", "Field 'name' is missing or empty"));
        }
    }
}


To run this code, ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.14.0</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:4.14.0'