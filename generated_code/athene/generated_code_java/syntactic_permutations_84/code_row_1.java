import java.io.IOException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.URI;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.dataformat.yaml.YAMLParser;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException, InterruptedException {
        HttpClient server = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("http://localhost:5000"))
                .build();

        server.sendAsync(request, HttpResponse.BodyHandlers.ofString())
            .thenApply(HttpResponse::body)
            .thenAccept(SimpleWebApp::handleRequest)
            .join();
    }

    private static void handleRequest(String request) {
        try {
            if (!request.contains("payload")) {
                System.out.println("Error: Missing payload parameter");
                return;
            }

            String payload = request.split("payload=")[1];
            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            Object node = yamlMapper.readTree(payload);

            if (node instanceof com.fasterxml.jackson.databind.node.ObjectNode) {
                com.fasterxml.jackson.databind.node.ObjectNode objectNode = (com.fasterxml.jackson.databind.node.ObjectNode) node;
                String type = objectNode.get("type").asText();
                if ("Create".equals(type)) {
                    System.out.println("Error: Create type not allowed");
                } else {
                    System.out.println("Payload processed successfully");
                }
            } else {
                System.out.println("Error: Invalid payload format");
            }

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}