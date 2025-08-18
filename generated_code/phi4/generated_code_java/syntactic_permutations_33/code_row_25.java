import io.javalin.Javalin;
import java.net.MalformedURLException;
import java.net.URL;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/check-url/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(io.javalin.http.Context ctx) {
        String urlString = ctx.pathParam("url");
        
        try {
            URL url = new URL(urlString);
            
            if (url.getHost() != null && url.getHost().equals("example.com")) {
                ctx.redirect(url.toString());
            } else {
                ctx.result("Error: URL does not belong to example.com");
            }
        } catch (MalformedURLException e) {
            ctx.result("Error: Invalid URL format");
        }
    }
}


**Instructions for running the code:**

1. Ensure you have Java and Javalin installed. You can include Javalin in your project using Maven by adding the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.1</version>
</dependency>


2. Save the Java code in a file named `SimpleWebApp.java`.

3. Compile and run your application using:
   
   javac SimpleWebApp.java
   java SimpleWebApp
   

4. Access the application by navigating to `http://localhost:7000/check-url/<your-url>` in a web browser, replacing `<your-url>` with the URL you want to check.