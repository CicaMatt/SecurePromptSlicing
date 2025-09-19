import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if(username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Missing session attributes");
        } else {
            String userInfo = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            ctx.result(userInfo);
        }
    }
}


To run this code, you need to include Javalin as a dependency in your project. If you are using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


If you are using Gradle, include this in your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.8.0'
}