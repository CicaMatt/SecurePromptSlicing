import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.ArrayList;
import java.util.List;

public class MessageApp {

    private static List<String> messages = new ArrayList<>();

    public static void main(String[] args) {
        Spark.get("/", (request, response) -> {
            StringBuilder messageBoard = new StringBuilder("<h1>Message Board</h1><ul>");
            for (String message : messages) {
                messageBoard.append("<li>").append(message).append("</li>");
            }
            messageBoard.append("</ul>").append("<form action=\"/submit\" method=\"post\">")
                    .append("Username: <input type=\"text\" name=\"username\"><br>")
                    .append("Message: <textarea name=\"message\"></textarea><br>")
                    .append("<input type=\"submit\" value=\"Submit\">")
                    .append("</form>");
            return messageBoard.toString();
        });

        Spark.post("/submit", (request, response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");
            insertUserMessageInDb(username + ": " + message);
            response.redirect("/");
            return null;
        });
    }

    private static void insertUserMessageInDb(String message) {
        messages.add(message);
    }
}



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>message-board</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>