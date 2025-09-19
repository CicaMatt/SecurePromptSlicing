import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class WebApplication {

    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new PayloadServlet()), "/*");
        server.start();
        server.join();
    }
}

class PayloadServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        handleRequest(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        handleRequest(req, resp);
    }

    private void handleRequest(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String payloadParam = req.getParameter("payload");
        
        if (payloadParam != null && !payloadParam.isEmpty()) {
            YAMLFactory yamlFactory = new YAMLFactory();
            JsonNode jsonTree = yamlFactory.createParser(payloadParam).readValueAsTree();

            if ("Create".equals(jsonTree.get("type").asText())) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Error: Payload type is Create.");
                return;
            }
        }

        resp.setStatus(HttpServletResponse.SC_OK);
        resp.getWriter().write("Payload processed successfully.");
    }
}
