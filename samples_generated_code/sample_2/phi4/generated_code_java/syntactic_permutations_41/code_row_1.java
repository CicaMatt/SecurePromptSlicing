import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe";
            String email = "johndoe@example.com";
            String ssn = "123-45-6789";

            String response = "<html>" +
                    "<head><title>User Info</title></head>" +
                    "<body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Social Security Number: " + ssn + "</p>" +
                    "</body>" +
                    "</html>";

            ctx.result(response);
        });
    }
}
