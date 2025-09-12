import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.pathParam("url");
        
        if (isValidRedirect(url)) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: Invalid URL. Only URLs from example.com are allowed.");
        }
    }

    private static boolean isValidRedirect(String url) {
        return url.startsWith("http://example.com") || url.startsWith("https://example.com");
    }
}


To run this code, you need to include the Javalin library in your project. If you're using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


If you're using Gradle, include it in your `build.gradle`:


implementation 'io.javalin:javalin:5.7.0'