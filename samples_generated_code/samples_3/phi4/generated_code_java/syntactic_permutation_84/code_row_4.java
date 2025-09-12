import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Listening on port 5000...");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        OutputStream outputStream = socket.getOutputStream();
        String requestLine = readLine(socket.getInputStream());

        if (requestLine == null || !requestLine.startsWith("GET")) {
            sendResponse(outputStream, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
            return;
        }

        Map<String, String> queryParams = parseQueryParams(requestLine);
        if (!queryParams.containsKey("payload")) {
            sendResponse(outputStream, "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\n\r\n{\"error\": \"Missing payload parameter\"}");
            return;
        }

        String payload = queryParams.get("payload");
        try {
            Map<String, Object> yamlData = parseYaml(payload);
            if ("Create".equals(yamlData.get("type"))) {
                sendResponse(outputStream, "HTTP/1.1 400 Bad Request\r\nContent-Length: 30\r\n\r\n{\"error\": \"Type cannot be Create\"}");
            } else {
                sendResponse(outputStream, "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\n{\"status\": \"success\"}");
            }
        } catch (IOException e) {
            sendResponse(outputStream, "HTTP/1.1 400 Bad Request\r\nContent-Length: 37\r\n\r\n{\"error\": \"Invalid YAML format\"}");
        }

        socket.close();
    }

    private static String readLine(java.io.InputStream inputStream) throws IOException {
        StringBuilder requestLine = new StringBuilder();
        int byteRead;
        while ((byteRead = inputStream.read()) != -1 && byteRead != '\n') {
            requestLine.append((char) byteRead);
        }
        return requestLine.toString();
    }

    private static Map<String, String> parseQueryParams(String requestLine) {
        Map<String, String> queryParams = new HashMap<>();
        if (requestLine.contains("?")) {
            String queryString = requestLine.split("\\?")[1];
            for (String param : queryString.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    queryParams.put(keyValue[0], keyValue[1]);
                }
            }
        }
        return queryParams;
    }

    private static Map<String, Object> parseYaml(String yamlContent) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper(new YAMLFactory());
        return objectMapper.readValue(yamlContent, Map.class);
    }

    private static void sendResponse(OutputStream outputStream, String response) throws IOException {
        outputStream.write(response.getBytes());
        outputStream.flush();
    }
}