import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleWebApp {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(5000)) {
            System.out.println("Listening on port 5000...");

            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))) {
            String requestLine = in.readLine();

            if (requestLine == null || !requestLine.startsWith("POST")) {
                sendErrorResponse(clientSocket, "Invalid Request");
                return;
            }

            StringBuilder payloadBuilder = new StringBuilder();
            String line;

            while (!(line = in.readLine()).isEmpty()) {
                payloadBuilder.append(line);
            }

            String payload = payloadBuilder.toString();

            if (payload.isEmpty() || !payload.contains("type")) {
                sendErrorResponse(clientSocket, "Payload parameter is missing or incomplete");
                return;
            }

            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            JsonNode rootNode;

            try {
                rootNode = yamlMapper.readTree(payload);
            } catch (IOException e) {
                sendErrorResponse(clientSocket, "Invalid YAML payload");
                return;
            }

            String type = rootNode.path("type").asText(null);

            if ("Create".equalsIgnoreCase(type)) {
                sendErrorResponse(clientSocket, "Type Create is not allowed");
                return;
            }

            sendSuccessResponse(clientSocket);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void sendErrorResponse(Socket clientSocket, String message) throws IOException {
        StringBuilder response = new StringBuilder("HTTP/1.1 400 Bad Request\r\n")
                .append("Content-Type: text/plain\r\n")
                .append("\r\n")
                .append(message);

        clientSocket.getOutputStream().write(response.toString().getBytes());
    }

    private static void sendSuccessResponse(Socket clientSocket) throws IOException {
        StringBuilder response = new StringBuilder("HTTP/1.1 200 OK\r\n")
                .append("Content-Type: text/plain\r\n")
                .append("\r\n")
                .append("Request processed successfully");

        clientSocket.getOutputStream().write(response.toString().getBytes());
    }
}


Dependencies needed:
- Jackson library for YAML parsing.
  
Add the following dependencies to your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.15.0</version>
    </dependency>
</dependencies>