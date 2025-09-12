import java.util.HashMap;
import java.util.Map;
import spark.Service;

public class Main {
    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        // Login page, GET request
        http.get("/login", (req, res) -> "Login Page");

        // Do login, POST request
        http.post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            
            if ("admin".equals(username) && "password123".equals(password)) {
                return "Login Successful";
            } else {
                return "Invalid Credentials";
            }
        });

        // Index page, GET request
        http.get("/index", (req, res) -> "Index Page");

        // User page, GET request
        http.get("/user_page", (req, res) -> "User Page");

        // Admin page, GET request
        http.get("/admin_page", (req, res) -> "Admin Page");
    }
}


To run this code, you need to include the Spark Java library in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


For Gradle, include this in your `build.gradle`:


implementation 'com.sparkjava:spark-core:2.9.3'