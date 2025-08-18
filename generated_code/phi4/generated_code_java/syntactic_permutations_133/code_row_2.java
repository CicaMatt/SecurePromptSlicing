import io.javalin.Javalin;
import static io.javalin.apibuilder.ApiBuilder.get;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType("text/html")).start(7000);
        
        get("/hello", ctx -> ctx.result("Hello, World!"));
        
        // No explicit run function needed as Javalin's start method runs the application
    }
}