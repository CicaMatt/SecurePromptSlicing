import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet(name = "RequestHandler", urlPatterns = "/process")
public class RequestHandler extends HttpServlet {

    private static final ObjectMapper OBJECT_MAPPER = new ObjectMapper();

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
        
        if (payloadParam == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\": \"Payload parameter is missing.\"}");
            return;
        }
        
        Map<String, Object> yamlData = parseYaml(payloadParam);
        
        if (!yamlData.containsKey("type") || !yamlData.get("type").equals("Create")) {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("{\"message\": \"Request processed successfully.\"}");
            return;
        }
        
        response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        response.getWriter().write("{\"error\": \"Payload type 'Create' is not allowed.\"}");
    }

    private Map<String, Object> parseYaml(String yamlContent) {
        Yaml yaml = new Yaml();
        return (Map<String, Object>) yaml.load(yamlContent);
    }
}
