import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClientRequest(clientSocket);
        }
    }

    private static void handleClientRequest(Socket clientSocket) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        StringBuilder requestBuilder = new StringBuilder();
        int inputStreamData;
        while ((inputStreamData = clientSocket.getInputStream().read()) != -1) {
            requestBuilder.append((char) inputStreamData);
        }
        String request = requestBuilder.toString();
        Map<String, String> params = parseQuery(request);
        if (!params.containsKey("payload")) {
            sendResponse(clientSocket, "Error: payload parameter is missing");
            return;
        }
        Yaml yaml = new Yaml(new Constructor(Map.class));
        try {
            Map<String, Object> payloadMap = yaml.load(params.get("payload"));
            if ("Create".equals(payloadMap.get("type"))) {
                sendResponse(clientSocket, "Error: type Create is not allowed");
            } else {
                sendResponse(clientSocket, "Request processed successfully");
            }
        } catch (Exception e) {
            sendResponse(clientSocket, "Error: invalid YAML format");
        }
    }

    private static Map<String, String> parseQuery(String request) {
        String[] split = request.split("\\?");
        if (split.length < 2) return new HashMap<>();
        String query = split[1];
        String[] params = query.split("&");
        Map<String, String> map = new HashMap<>();
        for (String param : params) {
            String[] keyValue = param.split("=");
            if (keyValue.length == 2) {
                map.put(keyValue[0], keyValue[1]);
            }
        }
        return map;
    }

    private static void sendResponse(Socket clientSocket, String response) throws IOException {
        clientSocket.getOutputStream().write(response.getBytes());
        clientSocket.close();
    }
}



<!-- Add this dependency to your pom.xml if using Maven -->
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.13.0</version>
</dependency>
<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.29</version>
</dependency>