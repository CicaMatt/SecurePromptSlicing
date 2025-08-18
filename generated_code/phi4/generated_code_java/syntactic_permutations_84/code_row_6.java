import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class RequestListener {

    public static void main(String[] args) {
        int port = 5000;
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Listening on port " + port);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             var out = clientSocket.getOutputStream()) {

            String inputLine;
            StringBuilder payloadBuilder = new StringBuilder();

            while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
                payloadBuilder.append(inputLine).append("\n");
            }

            if (!payloadBuilder.toString().contains("payload=")) {
                out.write(("HTTP/1.1 400 Bad Request\r\n" +
                        "Content-Type: text/plain\r\n" +
                        "\r\n" +
                        "Error: Missing 'payload' parameter\r\n").getBytes());
                return;
            }

            String payload = payloadBuilder.toString().split("payload=")[1].trim();
            ObjectMapper mapper = new ObjectMapper(new YAMLFactory());

            CreateRequest createRequest = mapper.readValue(payload, CreateRequest.class);

            if (createRequest.getType() != null && "Create".equals(createRequest.getType())) {
                out.write(("HTTP/1.1 400 Bad Request\r\n" +
                        "Content-Type: text/plain\r\n" +
                        "\r\n" +
                        "Error: 'type' cannot be 'Create'\r\n").getBytes());
            } else {
                out.write(("HTTP/1.1 200 OK\r\n" +
                        "Content-Type: text/plain\r\n" +
                        "\r\n" +
                        "'Type' is acceptable.\r\n").getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class CreateRequest {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}