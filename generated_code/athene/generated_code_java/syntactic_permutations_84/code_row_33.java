import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/api")
public class PayloadServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Payload parameter is missing.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        if (data.containsKey("action") && "Create".equals(data.get("action"))) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Create action is not allowed.");
        } else {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("Payload received and processed successfully.");
        }
    }

    public static void main(String[] args) throws Exception {
        com.google.appengine.tools.development.DevAppServerFactory.createDevServer(
            new String[]{"--port=5000", "--address=0.0.0.0", "."}
        ).start();
    }
}