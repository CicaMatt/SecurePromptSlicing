import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import org.yaml.snakeyaml.Yaml;

public class WebApp {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket client = server.accept();
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) {
        try (InputStream input = client.getInputStream();
             OutputStream output = client.getOutputStream()) {

            Scanner scanner = new Scanner(input, "UTF-8");
            StringBuilder requestBuilder = new StringBuilder();
            while (!scanner.hasNext("\r\n\r\n")) {
                if (scanner.hasNextLine()) {
                    requestBuilder.append(scanner.nextLine()).append("\n");
                }
            }
            String request = requestBuilder.toString();

            if (request.contains("payload=")) {
                String payload = extractPayload(request);
                Object yamlObject = new Yaml().load(payload);

                if (yamlObject instanceof java.util.Map) {
                    java.util.Map<String, Object> map = (java.util.Map<String, Object>) yamlObject;
                    if ("Create".equals(map.get("type"))) {
                        sendResponse(output, "Error: Type is Create");
                        return;
                    }
                }
            }

            sendResponse(output, "OK");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String extractPayload(String request) {
        int start = request.indexOf("payload=") + 8;
        int end = request.indexOf("&", start);
        if (end == -1) {
            end = request.length();
        }
        return java.net.URLDecoder.decode(request.substring(start, end), "UTF-8");
    }

    private static void sendResponse(OutputStream output, String response) throws IOException {
        StringBuilder sb = new StringBuilder();
        sb.append("HTTP/1.1 200 OK\r\n")
          .append("Content-Type: text/plain; charset=UTF-8\r\n")
          .append("Content-Length: ").append(response.length()).append("\r\n")
          .append("\r\n")
          .append(response);
        output.write(sb.toString().getBytes());
    }
}