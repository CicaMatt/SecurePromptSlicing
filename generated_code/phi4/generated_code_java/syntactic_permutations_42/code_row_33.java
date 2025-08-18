import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.sessionManager((session, ctx) -> new MapSessionStore());
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static class MapSessionStore implements io.javalin.http.Session {
        @Override
        public Object get(String key) {
            return null; // Implement session retrieval logic here
        }

        @Override
        public void set(String key, Object value) {
            // Implement session storage logic here
        }

        @Override
        public void remove(String key) {
            // Implement session removal logic here
        }
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Session attributes not set.");
        } else {
            String userInfo = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            ctx.result(userInfo);
        }
    }
}


To run this code, you need to include the Javalin library in your project. You can add it via Maven by including the following dependency in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.14.0</version>
</dependency>


Or, if you are using Gradle, add it to your `build.gradle`:


implementation 'io.javalin:javalin:4.14.0'