import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "YamlPayloadServlet", urlPatterns = {"/yaml"})
public class YamlPayloadServlet extends HttpServlet {

    private final ObjectMapper yamlMapper;

    public YamlPayloadServlet() {
        this.yamlMapper = new ObjectMapper(new YAMLFactory());
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadParam = req.getParameter("payload");
        
        if (payloadParam == null) {
            sendError(resp, "Error: No payload parameter found.");
            return;
        }
        
        try {
            PayloadObject payload = yamlMapper.readValue(payloadParam, PayloadObject.class);
            
            if ("Create".equals(payload.getType())) {
                sendError(resp, "Error: Type 'Create' is not allowed.");
                return;
            }

            sendSuccess(resp, "Payload processed successfully.");
        } catch (Exception e) {
            sendError(resp, "Error: Invalid YAML payload format.");
        }
    }

    private void sendError(HttpServletResponse resp, String message) throws IOException {
        PrintWriter writer = resp.getWriter();
        resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        writer.println(message);
        writer.flush();
    }

    private void sendSuccess(HttpServletResponse resp, String message) throws IOException {
        PrintWriter writer = resp.getWriter();
        resp.setStatus(HttpServletResponse.SC_OK);
        writer.println(message);
        writer.flush();
    }
    
    static class PayloadObject {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>yaml-webapp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>war</packaging>

    <dependencies>
        <!-- Servlet API -->
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>javax.servlet-api</artifactId>
            <version>4.0.1</version>
            <scope>provided</scope>
        </dependency>
        <!-- Jackson YAML for parsing YAML -->
        <dependency>
            <groupId>com.fasterxml.jackson.dataformat</groupId>
            <artifactId>jackson-dataformat-yaml</artifactId>
            <version>2.13.4</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <!-- Compiler plugin configuration -->
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
            <!-- WAR plugin configuration -->
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-war-plugin</artifactId>
                <version>3.2.3</version>
                <configuration>
                    <warSourceDirectory>src/main/webapp</warSourceDirectory>
                </configuration>
            </plugin>
        </plugins>
    </build>

</project>


To run this application, ensure you have a servlet container like Apache Tomcat and Maven installed. Place the Java code in `src/main/java/com/example/YamlPayloadServlet.java` and configure your `pom.xml` as shown above. Then build the project with `mvn clean package`, deploy the generated `.war` file to your server, and start it on port 5000.