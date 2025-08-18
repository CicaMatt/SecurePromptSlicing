import spark.Spark;

public class CheckModApp {

    public static void main(String[] args) {
        Spark.get("/check_mod", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");
            return check_mod(username, password);
        });
    }

    private static String check_mod(String username, String password) {
        // Example hardcoded credentials for demonstration purposes
        if ("admin".equals(username) && "secret".equals(password)) {
            return "true";
        }
        return "false";
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>check-mod-app</artifactId>
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
                    <source>1.8</source>
                    <target>1.8</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>