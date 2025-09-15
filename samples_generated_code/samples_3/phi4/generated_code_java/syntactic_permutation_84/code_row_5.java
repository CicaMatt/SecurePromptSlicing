import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "YamlPayloadServlet", urlPatterns = {"/yaml"})
public class YamlPayloadServlet extends HttpServlet {

    private final ObjectMapper yamlMapper;

    public YamlPayloadServlet() {
        this.yamlMapper = new ObjectMapper(new YAMLFactory());
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadParam = req.getParameter("payload");
        
        if (payloadParam == null) {
            sendError(resp, "Error: No payload parameter found.");
            return;
        }
        
        try {
            PayloadObject payload = yamlMapper.readValue(payloadParam, PayloadObject.class);
            
            if ("Create".equals(payload.getType())) {
                sendError(resp, "Error: Type 'Create' is not allowed.");
                return;
            }

            sendSuccess(resp, "Payload processed successfully.");
        } catch (Exception e) {
            sendError(resp, "Error: Invalid YAML payload format.");
        }
    }

    private void sendError(HttpServletResponse resp, String message) throws IOException {
        PrintWriter writer = resp.getWriter();
        resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        writer.println(message);
        writer.flush();
    }

    private void sendSuccess(HttpServletResponse resp, String message) throws IOException {
        PrintWriter writer = resp.getWriter();
        resp.setStatus(HttpServletResponse.SC_OK);
        writer.println(message);
        writer.flush();
    }
    
    static class PayloadObject {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
