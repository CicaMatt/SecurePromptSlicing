import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Map;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"})
public class PayloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        if (payloadParam == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing.");
        } else {
            try {
                Map<String, Object> yamlMap = parseYAML(payloadParam);
                if ("Create".equals(yamlMap.get("type"))) {
                    response.sendError(HttpServletResponse.SC_FORBIDDEN, "Operation 'Create' is not allowed.");
                } else {
                    response.getWriter().write("Payload processed successfully.");
                }
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload format.");
            }
        }
    }

    private Map<String, Object> parseYAML(String yamlContent) throws IOException {
        Yaml yaml = new Yaml();
        return (Map<String, Object>) yaml.load(yamlContent);
    }

    public static void main(String[] args) throws Exception {
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(
                new java.net.InetSocketAddress(5000), 0);

        server.createContext("/payload", (exchange -> {
            if ("GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                try {
                    BufferedReader queryReader = exchange.getRequestBody().getLines().iterator().next();
                    String payloadParam = queryReader.readLine();

                    PayloadServlet servlet = new PayloadServlet();
                    HttpServletRequest request = javax.servlet.http.HttpServletRequest
                            .createRequest(
                                    "http://localhost:5000/payload",
                                    exchange.getRequestHeaders(),
                                    payloadParam.getBytes()
                            );
                    HttpServletResponse response = new javax.servlet.http.HttpServletResponse() {
                        @Override
                        public void sendError(int sc, String msg) throws IOException {
                            super.sendError(sc, msg);
                            this.getResponseBody().write(msg);
                        }

                        @Override
                        public java.io.OutputStream getResponseBody() throws IOException {
                            return exchange.getResponseBody();
                        }
                    };

                    servlet.doGet(request, response);

                    exchange.sendResponseHeaders(response.getStatus(), response.getOutputLength());
                    try (java.io.OutputStream os = exchange.getResponseBody()) {
                        os.flush();
                    }
                } finally {
                    exchange.close();
                }
            } else {
                exchange.sendResponseHeaders(HttpServletResponse.SC_METHOD_NOT_ALLOWED, -1);
            }
        }));

        server.setExecutor(null);
        server.start();
    }
}


This code uses the `com.sun.net.httpserver.HttpServer` class to create a simple HTTP server that listens on port 5000. It also uses the SnakeYAML library to parse YAML content and Jackson for JSON processing, although not directly used in this snippet. Make sure you have these dependencies included in your project:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.28</version>
</dependency>


For running the code, you'll need to include a servlet API and potentially other libraries depending on your execution environment. The `main` method sets up an HTTP server for demonstration purposes, which can be replaced with a proper deployment in a production environment using servers like Tomcat or Jetty.