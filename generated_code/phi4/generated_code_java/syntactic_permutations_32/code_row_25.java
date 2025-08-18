import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.pathParam("url");
        
        if (url.contains("example.com")) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: URL must be from example.com.");
        }
    }
}


To run this code, ensure you have Javalin included in your project dependencies. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


For Gradle, use:


implementation 'io.javalin:javalin:5.7.0'