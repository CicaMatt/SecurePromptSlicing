import org.yaml.snakeyaml.Yaml;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/process")
public class PayloadProcessor extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: No payload provided.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        if ("Create".equalsIgnoreCase((String) data.get("type"))) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Type Create is not allowed.");
            return;
        }

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write("Payload processed successfully.");
    }
}