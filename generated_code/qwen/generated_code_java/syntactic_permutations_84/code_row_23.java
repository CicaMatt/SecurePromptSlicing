import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/")
public class SimpleWebApp extends HttpServlet {
    private final ObjectMapper objectMapper = new ObjectMapper();
    private final Yaml yaml = new Yaml();

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.getWriter().write("payload parameter is not present");
        } else {
            try {
                Map<String, Object> payloadMap = yaml.load(payloadParam);
                if ("Create".equalsIgnoreCase((String) payloadMap.get("type"))) {
                    response.getWriter().write("Error: Type 'Create' is not allowed.");
                } else {
                    response.getWriter().write("Payload processed successfully");
                }
            } catch (Exception e) {
                response.getWriter().write("Failed to parse payload: " + e.getMessage());
            }
        }
    }

    public static void main(String[] args) throws Exception {
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(5000);
        tomcat.getConnector();

        org.apache.catalina.Context ctx = tomcat.addContext("", null);

        Tomcat.addServlet(ctx, "simpleWebApp", new SimpleWebApp());
        ctx.addServletMappingDecoded("/", "simpleWebApp");

        tomcat.start();
        tomcat.getServer().await();
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>

    <dependencies>
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>javax.servlet-api</artifactId>
            <version>4.0.1</version>
            <scope>provided</scope>
        </dependency>
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>2.0</version>
        </dependency>
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-databind</artifactId>
            <version>2.15.2</version>
        </dependency>
        <dependency>
            <groupId>org.apache.tomcat.embed</groupId>
            <artifactId>tomcat-embed-core</artifactId>
            <version>9.0.76</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.codehaus.mojo</groupId>
                <artifactId>exec-maven-plugin</artifactId>
                <version>3.1.0</version>
                <configuration>
                    <mainClass>SimpleWebApp</mainClass>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>