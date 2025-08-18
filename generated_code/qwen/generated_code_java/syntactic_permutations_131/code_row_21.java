import java.io.StringWriter;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Map<String, Object> env, Request request) {
        StringWriter writer = new StringWriter();
        STGroup group = (STGroup) env.get("templateGroup");
        ST template = group.getInstanceOf("pageTemplate");
        template.add("name", request.queryParams("name"));
        template.write(writer);
        return writer.toString();
    }

    public static String home(Request request, Response response) {
        Map<String, Object> env = (Map<String, Object>) request.attribute("env");
        return render_response_from_env(env, request);
    }
}

import org.stringtemplate.v4.ST;
import org.stringtemplate.v4.STGroup;

import java.util.HashMap;

class EnvironmentSetup {
    public static void main(String[] args) {
        STGroup group = new STGroup.String("<pageTemplate(name)>Hello, <name>!</pageTemplate>");
        Map<String, Object> env = new HashMap<>();
        env.put("templateGroup", group);
        Spark.before((request, response) -> request.attribute("env", env));
    }
}



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>spark-template-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.4</version>
        </dependency>
        <dependency>
            <groupId>org.antlr</groupId>
            <artifactId>ST4</artifactId>
            <version>4.3</version>
        </dependency>
    </dependencies>
</project>