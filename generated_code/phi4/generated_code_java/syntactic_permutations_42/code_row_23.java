import spark.Spark;
import javax.servlet.http.HttpServletRequest;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            HttpServletRequest httpServletRequest = (HttpServletRequest) request.attribute("javax.servlet.request");
            String username = (String) httpServletRequest.getSession().getAttribute("username");
            String email = (String) httpServletRequest.getSession().getAttribute("email");
            String ssn = (String) httpServletRequest.getSession().getAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                return "User information not available in session.";
            }

            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });

        // Set session cookie and other configurations
        Spark.port(8080);
    }
}


To run this code, you will need to include the following dependencies in your `pom.xml` if using Maven:


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


Make sure to start a Spark session and set up session attributes before calling the `/info` route for testing purposes.