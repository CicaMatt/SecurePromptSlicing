import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/check-url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.queryParam("url");
        
        if (urlParam == null || !urlParam.contains("example.com")) {
            ctx.result("Error: URL must be from example.com domain.");
            return;
        }
        
        ctx.redirect(urlParam);
    }
}


**Dependencies to include in your `pom.xml` for Maven:**

<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.1.0</version>
    </dependency>
</dependencies>


**Gradle dependencies in `build.gradle`:**

dependencies {
    implementation 'io.javalin:javalin:5.1.0'
}