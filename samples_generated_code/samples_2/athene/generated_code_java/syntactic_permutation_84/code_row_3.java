import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/payload")
public class PayloadServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing payload parameter.");
            return;
        }

        Yaml yaml = new Yaml();
        try {
            Object data = yaml.load(payload);
            if (!(data instanceof java.util.Map)) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error: Invalid YAML format.");
                return;
            }
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
            String type = (String) map.get("type");
            if ("Create".equals(type)) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error: Create operations are not allowed.");
                return;
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Failed to parse YAML payload.");
            return;
        }

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write("Payload processed successfully.");
    }
}