import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;

public class RequestHandler {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        try {
            StringBuilder requestBuilder = new StringBuilder();
            int c;
            while ((c = clientSocket.getInputStream().read()) != -1 && c != '\r') {
                requestBuilder.append((char) c);
            }
            String request = requestBuilder.toString();
            if (request.contains("payload=")) {
                String payloadPart = request.split("payload=")[1];
                ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
                Map<String, Object> payloadMap = yamlReader.readValue(payloadPart, Map.class);
                if ("Create".equals(payloadMap.get("type"))) {
                    clientSocket.getOutputStream().write("Error: Type is Create\n".getBytes());
                } else {
                    clientSocket.getOutputStream().write("Success\n".getBytes());
                }
            } else {
                clientSocket.getOutputStream().write("Error: No payload parameter found\n".getBytes());
            }
        } catch (Exception e) {
            clientSocket.getOutputStream().write("An error occurred\n".getBytes());
        } finally {
            clientSocket.close();
        }
    }
}