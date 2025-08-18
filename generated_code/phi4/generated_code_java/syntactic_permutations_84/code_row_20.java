import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"})
public class PayloadServlet extends HttpServlet {

    private final ObjectMapper yamlMapper = new ObjectMapper().configure(org.yaml.snakeyaml.DumperOptions.FlowStyle.BLOCK, true);

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String action = processRequest(request);
        if (action != null && "Create".equals(action)) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Operation type 'Create' is not allowed.");
        } else {
            response.getWriter().write("Request processed successfully.");
        }
    }

    private String processRequest(HttpServletRequest request) throws IOException {
        String payloadParam = request.getParameter("payload");
        if (payloadParam != null && !payloadParam.isEmpty()) {
            JsonNode rootNode = yamlMapper.readTree(payloadParam);
            return rootNode.has("type") ? rootNode.get("type").asText() : null;
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(5000);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        server.getHandler().addServletWithMapping(PayloadServlet.class, "/payload");
        System.out.println("Server started on port 5000. Press Ctrl+C to stop.");
        server.start();
        server.join();
    }
}


### Dependencies

To run this code, you need the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>11.0.15</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-servlet</artifactId>
        <version>11.0.15</version>
    </dependency>
</dependencies>