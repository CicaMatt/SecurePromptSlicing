import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;
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

        HttpServlet servlet = new PayloadServlet();
        context.addServlet(new ServletHolder(servlet), "/*");

        server.start();
        server.join();
    }

    static class PayloadServlet extends HttpServlet {
        private final YAMLMapper yamlMapper = new YAMLMapper();

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            handleRequest(req, resp);
        }

        @Override
        protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            handleRequest(req, resp);
        }

        private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String payloadParam = request.getParameter("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("{\"error\":\"Missing 'payload' parameter\"}");
                return;
            }

            try {
                Payload payload = yamlMapper.readValue(payloadParam, Payload.class);
                if ("Create".equals(payload.getType())) {
                    response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                    response.getWriter().write("{\"error\":\"Type 'Create' is not allowed\"}");
                } else {
                    response.setStatus(HttpServletResponse.SC_OK);
                    response.getWriter().write("{\"message\":\"Payload accepted\"}");
                }
            } catch (Exception e) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("{\"error\":\"Invalid YAML format\"}");
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
}