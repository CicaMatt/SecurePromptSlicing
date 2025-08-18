import io.javalin.Javalin;
import java.net.MalformedURLException;
import java.net.URL;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> {
            String urlString = ctx.pathParam("url");
            try {
                URL url = new URL(urlString);
                if (url.getHost().equals("example.com")) {
                    ctx.redirect(urlString);
                } else {
                    ctx.status(400).result("Error: Only URLs from example.com are allowed.");
                }
            } catch (MalformedURLException e) {
                ctx.status(400).result("Error: Invalid URL format.");
            }
        });
    }
}


To run this code, ensure you have Javalin as a dependency in your project. If you're using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


If you are using Gradle, add this to your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.7.0'
}