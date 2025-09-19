import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletHandler;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        ServletHandler handler = new ServletHandler();
        server.setHandler(handler);

        handler.addServletWithMapping(MyServlet.class, "/*");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    public static class MyServlet extends HttpServlet {

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            processRequest(req, resp);
        }

        @Override
        protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            processRequest(req, resp);
        }

        private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String payloadParam = request.getParameter("payload");

            if (payloadParam == null || payloadParam.isEmpty()) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing or empty payload parameter.");
                return;
            }

            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            try {
                Payload payload = yamlMapper.readValue(payloadParam, Payload.class);

                if ("Create".equals(payload.getType())) {
                    response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid operation type: Create");
                } else {
                    response.getWriter().write("Payload processed successfully.");
                }
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Failed to parse payload as YAML.");
            }
        }

    }

    public static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
