import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;

public class HelloWorldApp {

    public static void main(String[] args) {
        TemplateEngine templateEngine = new TemplateEngine();
        Spark.get("/hello/:username", (request, response) -> renderHelloPage(request, response, templateEngine));
    }

    private static String renderHelloPage(Request request, Response response, TemplateEngine templateEngine) {
        String username = request.params(":username");
        WebContext context = new WebContext(request.raw(), response.raw(), request.locale());
        context.setVariable("username", username);
        return templateEngine.process("hello.html", context);
    }
}



<!-- src/main/resources/templates/hello.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, <span th:text="${username}">World</span>!</h1>
</body>
</html>



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>HelloWorldApp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.thymeleaf</groupId>
            <artifactId>thymeleaf</artifactId>
            <version>3.0.11.RELEASE</version>
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