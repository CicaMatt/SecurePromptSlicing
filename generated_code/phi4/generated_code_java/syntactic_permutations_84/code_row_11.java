import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"})
public class PayloadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing or empty 'payload' parameter.");
            return;
        }
        
        Map<String, Object> yamlData = parseYaml(payloadParam);
        
        if (!yamlData.containsKey("type") || !"Create".equalsIgnoreCase((String) yamlData.get("type"))) {
            response.getWriter().write("Payload type is not Create.");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Type 'Create' is not allowed.");
        }
    }

    private Map<String, Object> parseYaml(String yamlContent) {
        Yaml yaml = new Yaml();
        try (InputStream in = new java.io.ByteArrayInputStream(yamlContent.getBytes())) {
            return yaml.load(in);
        } catch (IOException e) {
            throw new RuntimeException("Failed to parse YAML", e);
        }
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(5000);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        
        org.eclipse.jetty.servlet.ServletHolder holder = new org.eclipse.jetty.servlet.ServletHolder("PayloadServlet", PayloadServlet.class);
        server.getHandler().addServlet(holder, "/payload");
        
        server.start();
        server.join();
    }
}
