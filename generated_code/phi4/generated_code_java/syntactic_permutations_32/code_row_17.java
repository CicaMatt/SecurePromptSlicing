import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/redirect/{url}", ctx -> redirectInvalidUrl(ctx));
    }
    
    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.pathParam("url");
        
        if (isValidUrl(url)) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: URL is not from example.com.");
        }
    }
    
    private static boolean isValidUrl(String url) {
        return url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com");
    }
}


Note: To run this code, you need to include the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.1</version>
</dependency>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.9.1'