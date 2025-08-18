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

        context.addServlet(new ServletHolder(new RequestHandler()), "/*");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    static class RequestHandler extends HttpServlet {

        private final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            handleRequest(req, resp);
        }

        @Override
        protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            handleRequest(req, resp);
        }

        private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String contentType = request.getContentType();
            if (contentType == null || !contentType.startsWith("application/x-yaml")) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error: Request must be YAML format.");
                return;
            }

            try {
                Payload payload = yamlMapper.readValue(request.getInputStream(), Payload.class);

                if ("Create".equalsIgnoreCase(payload.getType())) {
                    response.setStatus(HttpServletResponse.SC_FORBIDDEN);
                    response.getWriter().write("Error: Create operation is not allowed.");
                } else {
                    response.setStatus(HttpServletResponse.SC_OK);
                    response.getWriter().write("Request processed successfully.");
                }
            } catch (Exception e) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error parsing YAML payload.");
            }
        }

    }

    static class Payload {

        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}