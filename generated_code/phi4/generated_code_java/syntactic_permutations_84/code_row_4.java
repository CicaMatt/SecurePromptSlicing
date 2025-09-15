import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.io.StringReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

@WebServlet(name = "SimpleWebApp", urlPatterns = {"/"}, loadOnStartup = 1)
public class SimpleWebApp extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }
    
    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing 'payload' parameter.");
            return;
        }
        
        try {
            Payload payload = parsePayload(payloadParam);

            if ("Create".equals(payload.getType())) {
                response.setStatus(HttpServletResponse.SC_FORBIDDEN);
                response.getWriter().write("Error: Type is Create.");
            } else {
                response.setStatus(HttpServletResponse.SC_OK);
                response.getWriter().write("Request processed successfully.");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error processing request.");
        }
    }

    private Payload parsePayload(String payloadStr) throws IOException {
        Yaml yaml = new Yaml(new Constructor(Payload.class));
        return yaml.load(payloadStr);
    }

    public static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(5000);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        server.getServletHandler().addServletWithMapping(SimpleWebApp.class, "/");
        server.start();
        server.join();
    }
}
