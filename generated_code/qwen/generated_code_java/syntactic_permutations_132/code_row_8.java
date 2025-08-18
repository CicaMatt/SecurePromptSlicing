import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class UsernameDecorator {

    public static void main(String[] args) {
        Spark.get("/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate(username);
            }
        });
    }

    private static String renderTemplate(String username) {
        // Simulating a template rendering process
        StringBuilder htmlContent = new StringBuilder();
        htmlContent.append("<html>")
                   .append("<body>")
                   .append("<h1>Welcome, ").append(username).append("!</h1>")
                   .append("</body>")
                   .append("</html>");
        return htmlContent.toString();
    }
}



<!-- pom.xml for Maven to include Spark dependency -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>username-decorator</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>