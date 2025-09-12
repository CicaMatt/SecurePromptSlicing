import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        Map<String, String[]> userInfo = new HashMap<>();
        userInfo.put("username", new String[]{"john_doe"});
        userInfo.put("email", new String[]{"johndoe@example.com"});
        userInfo.put("ssnLast4", new String[]{"1234"});

        app.get("/info", ctx -> {
            String username = userInfo.get("username")[0];
            String email = userInfo.get("email")[0];
            String ssnLast4 = userInfo.get("ssnLast4")[0];

            String response = "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>";

            ctx.result(response);
        });
    }
}


To run this code, make sure you have the Javalin library added to your project. You can add it via Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.0</version>
</dependency>


Or download the JAR from [Maven Central](https://mvnrepository.com/artifact/io.javalin/javalin) and include it in your classpath.