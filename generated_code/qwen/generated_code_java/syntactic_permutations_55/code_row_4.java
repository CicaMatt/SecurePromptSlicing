import spark.Request;
import spark.Response;
import spark.Spark;

public class WebServer {

    public static void main(String[] args) {
        Spark.get("/login", (Request req, Response res) -> login(req, res));
        Spark.post("/do_login", (Request req, Response res) -> doLogin(req, res));
        Spark.get("/", (Request req, Response res) -> index(req, res));
        Spark.get("/user_page", (Request req, Response res) -> userPage(req, res));
        Spark.get("/admin_page", (Request req, Response res) -> adminPage(req, res));
    }

    public static String login(Request req, Response res) {
        return "Please log in.";
    }

    public static String doLogin(Request req, Response res) {
        String username = req.queryParams("username");
        String password = req.queryParams("password");
        if ("admin".equals(username) && "password123".equals(password)) {
            res.redirect("/user_page");
            return "";
        } else {
            res.status(401);
            return "Login failed.";
        }
    }

    public static String index(Request req, Response res) {
        return "Welcome to the homepage!";
    }

    public static String userPage(Request req, Response res) {
        return "This is the user page.";
    }

    public static String adminPage(Request req, Response res) {
        return "This is the admin page.";
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webserver</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>