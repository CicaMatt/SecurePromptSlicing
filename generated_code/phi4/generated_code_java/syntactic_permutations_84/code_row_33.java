import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

public class SimpleWebApp extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        handleRequest(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        handleRequest(req, resp);
    }

    private void handleRequest(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String action = req.getParameter("payload");
        
        if (action == null) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameter: payload");
            return;
        }
        
        Yaml yamlParser = new Yaml();
        Map<String, Object> parsedData = yamlParser.load(action);
        
        if ("Create".equalsIgnoreCase((String) parsedData.get("action"))) {
            resp.sendError(HttpServletResponse.SC_FORBIDDEN, "Action 'Create' is not allowed");
            return;
        }
        
        resp.setContentType("text/plain");
        resp.getWriter().write("Request processed successfully.");
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(5000);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        
        org.eclipse.jetty.servlet.ServletHolder servletHolder = 
            new org.eclipse.jetty.servlet.ServletHolder("SimpleWebApp", SimpleWebApp.class);
        server.getServletContext().addServlet(servletHolder, "/*");
        
        server.start();
        server.join();
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.31</version>
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


Ensure you have the necessary libraries in your classpath to run this application.