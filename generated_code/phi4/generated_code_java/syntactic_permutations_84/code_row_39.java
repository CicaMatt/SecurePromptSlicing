import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"})
public class PayloadServlet extends HttpServlet {

    private final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing.");
            return;
        }

        try {
            Payload payload = yamlMapper.readValue(payloadParam, Payload.class);
            
            if (!"Create".equals(payload.getType())) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid type. Expected 'Create'.");
                return;
            }
            
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Failed to parse YAML payload.");
            return;
        }

        response.setStatus(HttpServletResponse.SC_OK);
    }

    private static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
