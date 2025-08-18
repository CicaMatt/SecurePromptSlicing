import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);
        
        app.get("/redirect/:url", ctx -> {
            String urlParam = ctx.pathParam("url");
            redirectInvalidUrl(ctx, urlParam);
        });
    }

    private static void redirectInvalidUrl(Context ctx, String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: URL must be from example.com");
        }
    }
}


To run this application:
- Ensure you have Javalin dependency in your `pom.xml` if using Maven, or equivalent setup for other build tools.
  
Example `pom.xml` dependency for Javalin:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


Compile and run the application, then access `http://localhost:7000/redirect/http%3A//example.com/somepage` to test the redirect functionality.