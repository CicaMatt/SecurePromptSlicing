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
            return null;
        });
    }

    private static void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into database: User - " + username + ", Message - " + message);
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>