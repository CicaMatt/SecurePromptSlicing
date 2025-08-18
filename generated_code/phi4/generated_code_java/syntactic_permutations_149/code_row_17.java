import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/", ctx -> ctx.redirect("/"));

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insert_user_message_in_db(username, message);

            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            Map<String, Object> model = new HashMap<>();
            model.put("title", "Welcome Page");
            ctx.render(model);
        });
    }

    public static void insert_user_message_in_db(String username, String message) {
        // Simulate database insertion logic
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}


To make this code runnable:

1. Add dependencies for Javalin and a templating engine like Mustache in your `pom.xml` if using Maven or equivalent configuration for other build tools.


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.11.0</version>
</dependency>

<dependency>
    <groupId>com.github.spullara.mustache.java</groupId>
    <artifactId>compiler</artifactId>
    <version>0.9.6</version>
</dependency>


2. Create an `index.html` file in the `src/main/resources/templates` directory with basic HTML content:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{{title}}</title>
</head>
<body>
    <h1>Welcome to the Main Page!</h1>
    <form action="/post" method="POST">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>


3. Ensure your project structure aligns with Maven conventions or adjust paths if using another build system.