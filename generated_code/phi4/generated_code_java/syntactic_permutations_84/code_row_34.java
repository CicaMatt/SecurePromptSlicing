import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "YAMLValidator", urlPatterns = {"/validate"}, loadOnStartup = 1)
public class YAMLValidator extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\": \"Missing 'payload' parameter.\"}");
            return;
        }

        try {
            Yaml yaml = new Yaml();
            Map<String, Object> parsedYAML = yaml.load(payloadParam);

            if (parsedYAML.containsKey("type") && "forbiddenType".equals(parsedYAML.get("type"))) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("{\"error\": \"Payload type is forbidden.\"}");
            } else {
                response.setStatus(HttpServletResponse.SC_OK);
                response.getWriter().write("{\"message\": \"Payload accepted.\"}");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"error\": \"Error parsing YAML payload.\"}");
        }
    }

    public static void main(String[] args) throws IOException {
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/validate", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                HttpServletRequest request = (HttpServletRequest) ((com.sun.net.httpserver.Headers) exchange.getHttpRequest().getHeaders()).getRequest();
                HttpServletResponse response = (HttpServletResponse) ((com.sun.net.httpserver.Headers) exchange.getResponseHeaders()).getResponse();
                
                new YAMLValidator().doGet(request, response);
            }
            exchange.sendResponseHeaders(response.getStatus(), 0);
        });
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}
