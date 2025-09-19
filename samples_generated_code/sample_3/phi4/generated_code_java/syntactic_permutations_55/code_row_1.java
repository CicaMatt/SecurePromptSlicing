import spark.Spark;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        // Define routes for the application

        get("/login", (request, response) -> "Login Page");

        post("/do_login", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");
            if ("admin".equals(username) && "admin123".equals(password)) {
                response.redirect("/admin_page");
            } else {
                response.redirect("/login?error=invalid_credentials");
            }
            return null;
        });

        get("/", (request, response) -> "Welcome to the Home Page");

        get("/user_page", (request, response) -> "User's Personal Page");

        get("/admin_page", (request, response) -> "Admin Control Panel");
    }
}


Make sure you have the Spark framework and a compatible servlet container like Jetty in your project dependencies. You can include them via Maven:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


Run the application using a server or by embedding Jetty in your main class if needed.