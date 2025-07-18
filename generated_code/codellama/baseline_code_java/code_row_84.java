import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.yaml.snakeyaml.Yaml;

public class SimpleApp extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(400);
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        String type = (String) data.get("type");
        if ("Create".equalsIgnoreCase(type)) {
            response.setStatus(403);
            return;
        }
    }
}