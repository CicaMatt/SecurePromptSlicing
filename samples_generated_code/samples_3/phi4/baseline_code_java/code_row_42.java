import io.javalin.Javalin;
import org.eclipse.jetty.http.HttpStatus;

public class WebApplication {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json")
                .start(7000);

        app.post("/checkName", ctx -> {
            String name = ctx.bodyAsClass(Map.class).get("name");
            if (name != null) {
                ctx.json(Map.of("message", "Name found: " + name));
            } else {
                ctx.status(HttpStatus.NOT_FOUND_404);
                ctx.json(Map.of("error", "Field 'name' not found"));
            }
        });
    }
}


### Dependencies

To run this code, you need to include the following dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.8.0</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>11.0.14</version>
    </dependency>
</dependencies>