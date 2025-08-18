import java.io.IOException;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new RequestHandler()), "/*");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    public static class RequestHandler extends HttpServlet {
        private static final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            processRequest(req, resp);
        }

        @Override
        protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            processRequest(req, resp);
        }

        private void processRequest(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String payloadParam = req.getParameter("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'payload' parameter.");
                return;
            }

            try {
                MyPayload myPayload = yamlMapper.readValue(payloadParam, MyPayload.class);
                if ("Create".equals(myPayload.getType())) {
                    resp.sendError(HttpServletResponse.SC_FORBIDDEN, "Type Create is not allowed.");
                } else {
                    resp.setStatus(HttpServletResponse.SC_OK);
                    resp.getWriter().write("Request processed successfully.");
                }
            } catch (Exception e) {
                resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML payload format.");
            }
        }

        private static class MyPayload {
            private String type;

            public String getType() {
                return type;
            }

            public void setType(String type) {
                this.type = type;
            }
        }
    }
}


To run this code, you need to include the following dependencies in your project:

- Jetty server: For creating a simple web server.
- Jackson YAML: For parsing YAML payloads.

You can add these dependencies using Maven by including them in your `pom.xml` file:


<dependencies>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>11.0.12</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-servlet</artifactId>
        <version>11.0.12</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.13.3</version>
    </dependency>
</dependencies>