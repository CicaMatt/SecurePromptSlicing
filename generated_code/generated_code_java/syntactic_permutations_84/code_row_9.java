import java.util.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.yaml.snakeyaml.Yaml;

public class Servlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // check if payload parameter is present in the request
        String payload = request.getParameter("payload");
        if (payload == null || payload.trim().isEmpty()) {
            response.setStatus(400);
            response.sendError(400, "Payload parameter missing");
            return;
        }
        
        // parse the payload as YAML
        Map<String, Object> data = new HashMap<>();
        try {
            data = (Map<String, Object>) new Yaml().load(payload);
        } catch (Exception e) {
            response.setStatus(400);
            response.sendError(400, "Invalid payload format");
            return;
        }
        
        // check if the type is Create
        String type = (String) data.get("type");
        if (!type.equals("Create")) {
            response.setStatus(400);
            response.sendError(400, "Invalid payload type");
            return;
        }
        
        // write the output as JSON
        String json = new Gson().toJson(data);
        response.setContentType("application/json");
        response.getWriter().write(json);
    }
}