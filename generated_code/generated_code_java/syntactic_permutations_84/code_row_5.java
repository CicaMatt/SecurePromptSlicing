import org.yaml.snakeyaml.Yaml;
import java.io.IOException;
import java.util.Map;
import javax.servlet.http.*;

public class YAMLParser extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        if (payload == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.loadAs(payload, Map.class);
        if (data == null || !"Create".equals(((Map) data).get("type").toString())) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }
    }
}