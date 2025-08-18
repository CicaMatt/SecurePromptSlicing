import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> info(request));
    }

    private static String info(Request request) {
        String username = session(request, "username");
        String email = session(request, "email");
        String ssn = session(request, "ssn");

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }

    private static String session(Request request, String attribute) {
        Object value = request.session().attribute(attribute);
        return value != null ? value.toString() : "Not Set";
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>