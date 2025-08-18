import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/webapp")
public class SimpleWebApp extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Payload parameter is missing.");
            return;
        }

        try {
            Yaml yaml = new Yaml();
            Object data = yaml.load(payload);
            if (data instanceof java.util.Map) {
                java.util.Map<String, Object> mapData = (java.util.Map<String, Object>) data;
                String type = (String) mapData.get("type");
                if ("Create".equals(type)) {
                    response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                    response.getWriter().write("Error: Type 'Create' is not allowed.");
                    return;
                }
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Invalid YAML payload.");
            return;
        }

        // If no errors, the request can proceed
        response.getWriter().write("Request processed successfully.");
    }
}