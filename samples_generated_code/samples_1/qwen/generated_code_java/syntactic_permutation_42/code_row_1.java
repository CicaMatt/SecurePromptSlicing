import spark.Request;
import spark.Response;
import spark.Spark;

public class UserInfoApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> {
            String username = request.session().attribute("username");
            String email = request.session().attribute("email");
            String ssn = request.session().attribute("ssn");

            if (username == null || email == null || ssn == null) {
                response.status(404);
                return "User information not found.";
            }

            return "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
        });
    }
}



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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

    <build>
        <plugins>
            <plugin>
                <groupId>org.codehaus.mojo</groupId>
                <artifactId>exec-maven-plugin</artifactId>
                <version>3.0.0</version>
                <configuration>
                    <mainClass>UserInfoApp</mainClass>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>