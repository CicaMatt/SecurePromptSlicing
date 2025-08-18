import io.javalin.Javalin;
import java.net.MalformedURLException;
import java.net.URL;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.pathParam("url");
        try {
            URL url = new URL(urlParam);
            if (url.getHost() != null && url.getHost().endsWith("example.com")) {
                ctx.redirect(url.toString());
            } else {
                ctx.status(400).result("Error: The URL is not from example.com.");
            }
        } catch (MalformedURLException e) {
            ctx.status(400).result("Error: Invalid URL format.");
        }
    }
}


To run this code, ensure you have Javalin as a dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


For Gradle, include this in your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.8.0'
}