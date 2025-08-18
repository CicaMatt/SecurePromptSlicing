import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new MyServlet()), "/*");

        server.start();
        server.join();
    }

    public static class MyServlet extends HttpServlet {
        private final ObjectMapper yamlMapper;

        public MyServlet() {
            this.yamlMapper = new ObjectMapper(new YAMLFactory());
        }

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String param = req.getParameter("param");
            if (param == null || param.isEmpty()) {
                resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameter 'param'");
                return;
            }

            try {
                RequestData requestData = yamlMapper.readValue(param, RequestData.class);
                if ("Create".equalsIgnoreCase(requestData.getType())) {
                    resp.sendError(HttpServletResponse.SC_FORBIDDEN, "Operation 'Create' is not allowed");
                } else {
                    resp.getWriter().write("Request processed successfully.");
                }
            } catch (Exception e) {
                resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format");
            }
        }

        static class RequestData {
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


To run the above code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>11.0.15</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.4</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.13.4</version>
    </dependency>
</dependencies>