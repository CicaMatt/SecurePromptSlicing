import spark.Request;
import spark.Response;
import spark.Spark;

public class UserInfoApp {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/info", (Request request, Response response) -> {
            String username = "sampleUser";
            String email = "user@example.com";
            String ssnLastFour = "1234";
            return String.format("Username: %s%nEmail: %s%nSSN Last 4: %s", username, email, ssnLastFour);
        });
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>user-info-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>