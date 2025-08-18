import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            if (username == null || message == null) {
                ctx.status(400);
                ctx.result("Username and message are required.");
            } else {
                // Process the username and message as needed
                System.out.println("Received from " + username + ": " + message);
                ctx.status(200).result("Post received successfully");
            }
        });
    }
}


To run this code, you need to include Javalin in your project dependencies. If using Maven, add the following dependency in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


For Gradle, include this in your `build.gradle` file:


implementation 'io.javalin:javalin:5.8.0'