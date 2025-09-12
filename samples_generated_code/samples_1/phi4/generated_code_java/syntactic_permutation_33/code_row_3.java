import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectInvalidUrlApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/redirect", RedirectInvalidUrlApp::redirectInvalidUrl);
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.queryParam("url");

        if (url == null || !isValidUrl(url)) {
            ctx.status(400).result("{\"error\":\"Invalid URL\"}");
        } else {
            ctx.redirect(url);
        }
    }

    private static boolean isValidUrl(String url) {
        return url != null && (url.startsWith("http://") || url.startsWith("https://"));
    }
}


To run this code, you need to include the Javalin library in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.16.0</version>
</dependency>


For Gradle, include this in your `build.gradle`:


implementation 'io.javalin:javalin:4.16.0'