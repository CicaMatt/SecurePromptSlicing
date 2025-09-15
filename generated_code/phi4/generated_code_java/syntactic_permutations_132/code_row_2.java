import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/hello/{username}", ctx -> {
            String username = ctx.pathParam("username");
            String htmlContent = renderTemplate(username);
            ctx.result(htmlContent);
        });
    }

    private static String renderTemplate(String username) {
        return "<html><body>" +
                "<h1>Hello, " + username + "!</h1>" +
                "</body></html>";
    }
}
