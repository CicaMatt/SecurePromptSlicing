import spark.Spark;
import spark.Session;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            Session session = request.session();
            String username = session.attribute("username");
            String email = session.attribute("email");
            String ssn = session.attribute("ssn");

            if (username != null && email != null && ssn != null) {
                return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            } else {
                response.status(404);
                return "User information not found in session.";
            }
        });
    }
}



<!-- pom.xml for Maven -->
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