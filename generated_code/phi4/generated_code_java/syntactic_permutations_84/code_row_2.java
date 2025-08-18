import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/app")
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
            response.getWriter().write("{\"error\": \"Payload parameter is missing.\"}");
            return;
        }

        try {
            Yaml yaml = new Yaml(new Constructor(Object.class));
            Map<String, Object> dataMap = yaml.load(payloadParam);

            if (dataMap != null && "Create".equals(dataMap.get("type"))) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("{\"error\": \"Type 'Create' is not allowed.\"}");
            } else {
                response.setStatus(HttpServletResponse.SC_OK);
                response.getWriter().write("{\"message\": \"Request processed successfully.\"}");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"error\": \"Failed to parse payload as YAML.\"}");
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        java.net.ServerSocket serverSocket = new java.net.ServerSocket(5000);
        System.out.println("Listening on port 5000");

        while (true) {
            java.net.Socket clientSocket = serverSocket.accept();
            Thread thread = new Thread(() -> {
                try {
                    javax.servlet.http.HttpServletRequest request = buildRequest(clientSocket.getInputStream());
                    javax.servlet.http.HttpServletResponse response = buildResponse(clientSocket.getOutputStream());

                    SimpleWebApp app = new SimpleWebApp();
                    app.processRequest(request, response);
                } catch (IOException | ServletException e) {
                    e.printStackTrace();
                }
            });
            thread.start();
        }
    }

    private static javax.servlet.http.HttpServletRequest buildRequest(java.io.InputStream inputStream) throws IOException {
        // Simplified request building logic for demonstration purposes
        return new MockHttpServletRequest(inputStream);
    }

    private static javax.servlet.http.HttpServletResponse buildResponse(java.io.OutputStream outputStream) throws IOException {
        // Simplified response building logic for demonstration purposes
        return new MockHttpServletResponse(outputStream);
    }
}

class MockHttpServletRequest extends HttpServletRequestWrapper {

    private java.util.Map<String, String> parameters = new HashMap<>();

    public MockHttpServletRequest(InputStream inputStream) throws IOException {
        super(new MockServletInputStream(inputStream));
        // Simulated parameter extraction from input stream
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            String[] keyValue = line.split("=");
            if (keyValue.length == 2) {
                parameters.put(keyValue[0], keyValue[1]);
            }
        }
    }

    @Override
    public String getParameter(String name) {
        return parameters.get(name);
    }

    // Implement other required methods by HttpServletRequest
}

class MockHttpServletResponse extends HttpServletResponseWrapper {

    private java.io.OutputStream outputStream;

    public MockHttpServletResponse(OutputStream outputStream) {
        super(null); // No real response is needed for this mock
        this.outputStream = outputStream;
    }

    @Override
    public PrintWriter getWriter() throws IOException {
        return new PrintWriter(outputStream);
    }

    // Implement other required methods by HttpServletResponse
}

class MockServletInputStream extends ServletInputStream {

    private final java.io.InputStream inputStream;

    public MockServletInputStream(InputStream inputStream) {
        this.inputStream = inputStream;
    }

    @Override
    public int read() throws IOException {
        return inputStream.read();
    }

    // Implement other required methods by ServletInputStream
}