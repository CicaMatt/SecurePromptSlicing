import io.javalin.Javalin;

public class WebApp {

    public static void main(String[] args) {
        var app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/hello", ctx -> ctx.result("Hello, World!"));
    }
}