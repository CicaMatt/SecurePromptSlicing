import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> info());
    }

    private static String info() {
        String username = "exampleUser";
        String email = "user@example.com";
        String ssn = "123-45-6789";
        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}



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
            <version>2.9.4</version>
        </dependency>
    </dependencies>
</project>