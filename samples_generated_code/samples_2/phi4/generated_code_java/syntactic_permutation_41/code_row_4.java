import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Replace with actual user data retrieval logic
            String email = "johndoe@example.com"; // Replace with actual user data retrieval logic
            String ssnLast4 = "1234"; // Replace with actual user data retrieval logic

            String userInfo = "<html>" +
                    "<head><title>User Information</title></head>" +
                    "<body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>" +
                    "</body>" +
                    "</html>";

            ctx.result(userInfo);
        });
    }
}
