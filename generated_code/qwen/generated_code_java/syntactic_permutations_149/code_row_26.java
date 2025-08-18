import spark.Request;
import spark.Response;
import spark.Spark;

public class MessageApp {

    public static void main(String[] args) {
        Spark.post("/post", (Request request, Response response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");

            insert_user_message_in_db(username, message);

            response.redirect("/");
            return "";
        });

        Spark.get("/", (request, response) -> "Welcome to the Message App!");
    }

    private static void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User = " + username + ", Message = " + message);
        // Here you would add your actual database insertion logic
    }
}



<!-- pom.xml if using Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>message-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>