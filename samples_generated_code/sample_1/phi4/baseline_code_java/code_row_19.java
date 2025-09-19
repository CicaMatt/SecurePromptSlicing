import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.pathParam("url");
        
        if (urlParam.startsWith("http://example.com") || urlParam.startsWith("https://example.com")) {
            ctx.redirect(urlParam);
        } else {
            ctx.status(400).result("Error: URL must be from example.com.");
        }
    }
}


Make sure you have Javalin as a dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.5.0</version>
</dependency>


Or add the following to your `build.gradle` if you are using Gradle:


dependencies {
    implementation 'io.javalin:javalin:5.5.0'
}