import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Example data, replace with actual user information retrieval logic
            String email = "johndoe@example.com"; // Example data
            String ssnLastFour = "1234"; // Example data

            String responseHtml = "<html><head><title>User Info</title></head>"
                    + "<body><h1>Information Page</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>"
                    + "</body></html>";

            ctx.result(responseHtml);
        });
    }
}
