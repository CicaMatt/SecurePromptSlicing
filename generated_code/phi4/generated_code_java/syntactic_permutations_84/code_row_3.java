import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/process")
public class PayloadProcessorServlet extends HttpServlet {

    private static final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadParam = req.getParameter("payload");
        
        if (payloadParam == null) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing.");
            return;
        }

        try {
            Payload payload = yamlMapper.readValue(payloadParam, Payload.class);

            if ("Create".equalsIgnoreCase(payload.getType())) {
                resp.sendError(HttpServletResponse.SC_FORBIDDEN, "Operation type 'Create' is not allowed.");
                return;
            }
            
            resp.getWriter().write("Payload processed successfully.");
        } catch (Exception e) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML payload format.");
        }
    }

    private static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


**Note**: To run the above code, you will need to set up a Java web application environment using a servlet container like Apache Tomcat. Additionally, include the following dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>
</dependencies>