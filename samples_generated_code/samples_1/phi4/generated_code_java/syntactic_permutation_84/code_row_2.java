import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/"}, loadOnStartup = 1)
public class PayloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payloadParam = request.getParameter("payload");

        if (payloadParam == null || payloadParam.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing 'payload' parameter");
            return;
        }

        try {
            YAMLMapper yamlMapper = new YAMLMapper();
            PayloadData data = yamlMapper.readValue(payloadParam, PayloadData.class);

            if ("Create".equals(data.getType())) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error: 'type' should not be 'Create'");
            } else {
                response.setStatus(HttpServletResponse.SC_OK);
                response.getWriter().write("Payload processed successfully");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error parsing payload");
        }
    }

    private static class PayloadData {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>jakarta.servlet</groupId>
        <artifactId>jakarta.servlet-api</artifactId>
        <version>5.0.0</version>
        <scope>provided</scope>
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