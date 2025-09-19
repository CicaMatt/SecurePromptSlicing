import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"})
public class PayloadServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");

        if (payloadParam == null || payloadParam.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\":\"Payload parameter is missing\"}");
            return;
        }

        Yaml yaml = new Yaml();
        PayloadData data;

        try {
            data = yaml.loadAs(payloadParam, PayloadData.class);
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\":\"Invalid YAML format\"}");
            return;
        }

        if ("Create".equals(data.getType())) {
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            response.getWriter().write("{\"error\":\"Operation type 'Create' is not allowed\"}");
            return;
        }

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write("{\"message\":\"Payload processed successfully\"}");
    }

    private static class PayloadData {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
