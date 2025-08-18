import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.velocity.VelocityTemplateEngine;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res));
    }

    public static String render_response_from_env(Request request, Response response) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name != null) {
            model.put("name", name);
        } else {
            model.put("name", "World");
        }
        return new VelocityTemplateEngine().render(new ModelAndView(model, "templates/hello.vm"));
    }

    public static String home(Request request, Response response) {
        return render_response_from_env(request, response);
    }
}



<!-- pom.xml for Maven to include Spark and Velocity dependencies -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>spark-example</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.apache.velocity</groupId>
            <artifactId>velocity-engine-core</artifactId>
            <version>2.3</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.codehaus.mojo</groupId>
                <artifactId>exec-maven-plugin</artifactId>
                <version>3.0.0</version>
                <configuration>
                    <mainClass>Main</mainClass>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>



<!-- src/main/resources/templates/hello.vm -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
<h1>Hello, ${name}!</h1>
</body>
</html>