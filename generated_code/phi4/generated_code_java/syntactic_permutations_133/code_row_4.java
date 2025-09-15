import io.javalin.Javalin;
import static io.javalin.apibuilder.ApiBuilder.get;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        get("/hello", ctx -> ctx.result("Hello, World!"));
    }
}
