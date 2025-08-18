import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet(name = "YAMLCheckServlet", urlPatterns = {"/check-yaml"})
public class YAMLCheckServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'payload' parameter.");
            return;
        }
        
        try {
            Yaml yaml = new Yaml();
            Map<String, Object> parsedMap = yaml.load(payloadParam);
            
            if (parsedMap.containsKey("type") && "specificType".equals(parsedMap.get("type"))) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid 'type' in payload.");
            } else {
                response.getWriter().write("Payload is valid.");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Failed to parse YAML.");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To run this code as a standalone web application, you will need the following dependencies in your `pom.xml` if using Maven:


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
        <version>1.30</version>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.apache.tomcat.maven</groupId>
            <artifactId>tomcat7-maven-plugin</artifactId>
            <version>2.2</version>
            <configuration>
                <port>5000</port>
            </configuration>
        </plugin>
    </plugins>
</build>


This setup assumes you are using Apache Maven and Tomcat as the web server to deploy your servlet.