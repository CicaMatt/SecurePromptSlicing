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

        context.addServlet(new ServletHolder(new PayloadCheckServlet()), "/*");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    public static class PayloadCheckServlet extends HttpServlet {

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
            
            if (payloadParam != null) {
                YAMLFactory yamlFactory = new YAMLFactory();
                try {
                    CreateType createType = yamlFactory.createParser(payloadParam).parseValue(CreateType.class);

                    if ("Create".equals(createType.getType())) {
                        response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                        response.getWriter().write("Error: Type is Create");
                    } else {
                        response.setStatus(HttpServletResponse.SC_OK);
                        response.getWriter().write("Success: Valid payload");
                    }
                } catch (Exception e) {
                    response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                    response.getWriter().write("Error: Invalid YAML format");
                }
            } else {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error: Payload parameter is missing");
            }
        }

    }

    public static class CreateType {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
