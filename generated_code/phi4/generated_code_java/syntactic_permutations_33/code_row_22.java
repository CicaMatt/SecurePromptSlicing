import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/check-url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.queryParam("url");
        if (url != null && url.contains("example.com")) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: URL is not from example.com domain.");
        }
    }
}


To run this code, you need to include Javalin as a dependency. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


For Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:5.7.0'