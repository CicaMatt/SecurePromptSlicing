import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SimpleWebApp extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String contentType = req.getContentType();
        
        if (contentType == null || !contentType.equals("application/x-yaml")) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Error: Request must be of type 'application/x-yaml'");
            return;
        }

        StringBuilder payloadBuilder = new StringBuilder();
        try (BufferedReader reader = req.getReader()) {
            String line;
            while ((line = reader.readLine()) != null) {
                payloadBuilder.append(line);
            }
        }

        Yaml yaml = new Yaml();
        Object obj = yaml.load(payloadBuilder.toString());

        if (obj instanceof java.util.Map<?, ?>) {
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) obj;
            String type = (String) map.get("type");
            
            if ("Create".equalsIgnoreCase(type)) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Error: Create operations are not allowed.");
                return;
            }
        }

        resp.setStatus(HttpServletResponse.SC_OK);
        resp.getWriter().write("Request processed successfully.");
    }

    public static void main(String[] args) throws Exception {
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new SimpleWebApp());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}