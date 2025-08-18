import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletHandler;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SimpleWebApp {
    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        ServletHandler handler = new ServletHandler();
        server.setHandler(handler);

        handler.addServletWithMapping(MyServlet.class, "/*");

        server.start();
        server.join();
    }

    public static class MyServlet extends HttpServlet {

        private final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws Exception {
            processRequest(req, resp);
        }

        @Override
        protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws Exception {
            processRequest(req, resp);
        }

        private void processRequest(HttpServletRequest req, HttpServletResponse resp) throws Exception {
            String payload = req.getParameter("payload");
            if (payload == null) {
                resp.getWriter().write("Payload parameter is missing.");
                return;
            }

            MyPayload parsedPayload = yamlMapper.readValue(payload, MyPayload.class);

            if ("Create".equals(parsedPayload.getType())) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Error: Operation type 'Create' is not allowed.");
                return;
            }

            resp.getWriter().write("Request processed successfully.");
        }
    }

    public static class MyPayload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


To run this code, you need the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>11.0.15</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.14.1</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.14.1</version>
    </dependency>
</dependencies>