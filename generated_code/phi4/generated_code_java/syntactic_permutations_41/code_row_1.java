import io.javalin.Javalin;
import io.javalin.http.Context;

public class InfoApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", Context::userInfo);
    }

    private static void userInfo(Context ctx) {
        // Dummy data for illustration purposes
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        String response = "<html><head><title>User Info</title></head>"
                + "<body>"
                + "<h1>Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>"
                + "</body></html>";

        ctx.result(response);
    }
}
