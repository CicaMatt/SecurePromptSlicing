import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = ctx.cookie("username");
            String email = ctx.cookie("email");
            String last4Digits = ctx.cookie("last4digits");

            if (username != null && email != null && last4Digits != null) {
                ctx.result("<h1>User Information</h1>" +
                           "<p>Username: " + username + "</p>" +
                           "<p>Email: " + email + "</p>" +
                           "<p>Last 4 Digits of Card: " + last4Digits + "</p>");
            } else {
                ctx.status(400).result("<h1>Error</h1><p>User information is missing.</p>");
            }
        });
    }
}


To run this code, you need to have Javalin included in your project dependencies. If you're using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


For Gradle, include this in your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.8.0'
}