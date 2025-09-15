import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", WebApp::userInfoHandler);
    }

    private static void userInfoHandler(Context ctx) {
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4 = "1234";

        ctx.result(String.format(
            "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: %s</p>" +
                "<p>Email: %s</p>" +
                "<p>Last 4 of SSN: %s</p>" +
            "</body></html>",
            username, email, ssnLast4
        ));
    }
}
