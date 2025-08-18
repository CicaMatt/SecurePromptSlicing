import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new RequestHandler()), "/*");

        server.start();
        server.join();
    }

    static class RequestHandler extends HttpServlet {
        private final YAMLMapper yamlMapper = new YAMLMapper();

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            handleRequest(req, resp);
        }

        @Override
        protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            handleRequest(req, resp);
        }

        private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String payloadParam = request.getParameter("payload");
            if (payloadParam == null) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing.");
                return;
            }

            try {
                Map<String, Object> yamlMap = yamlMapper.readValue(payloadParam, Map.class);
                if ("Create".equals(yamlMap.get("type"))) {
                    response.sendError(HttpServletResponse.SC_FORBIDDEN, "Operation type 'Create' is not allowed.");
                } else {
                    response.setStatus(HttpServletResponse.SC_OK);
                    response.getWriter().write("Request processed successfully.");
                }
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format.");
            }
        }
    }
}


**Maven Dependencies (`pom.xml`):**


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>org.eclipse.jetty</groupId>
            <artifactId>jetty-server</artifactId>
            <version>11.0.14</version>
        </dependency>
        <dependency>
            <groupId>org.eclipse.jetty</groupId>
            <artifactId>jetty-servlet</artifactId>
            <version>11.0.14</version>
        </dependency>
        <dependency>
            <groupId>com.fasterxml.jackson.dataformat</groupId>
            <artifactId>jackson-dataformat-yaml</artifactId>
            <version>2.13.4</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>