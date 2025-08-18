import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insertUserMessageInDB(username, message);

            ctx.redirect("/");
        });
    }

    public static void insertUserMessageInDB(String username, String message) {
        // Assuming a method that inserts the user's message into the database
        // This is just a placeholder. Actual implementation will depend on your DB setup.
        System.out.println("Inserting into DB: " + "Username: " + username + ", Message: " + message);
    }
}


Make sure you have Javalin in your project dependencies to run this code:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.1.0</version> <!-- Use the latest version -->
</dependency>


This code uses Javalin, a lightweight web framework for Java. The `insertUserMessageInDB` function is a placeholder; you will need to implement actual database interaction according to your setup.