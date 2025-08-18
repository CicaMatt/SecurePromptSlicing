import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/info", SimpleWebApp::info);
    }

    public static String info(Request request, Response response) {
        String username = (String) request.session().attribute("username");
        String email = (String) request.session().attribute("email");
        String ssn = (String) request.session().attribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.status(401);
            return "User information not found in session.";
        }

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}



<!-- pom.xml for Maven to include Spark dependency -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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