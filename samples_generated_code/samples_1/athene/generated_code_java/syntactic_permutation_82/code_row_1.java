import java.io.*;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.URI;
import java.util.HashMap;
import java.util.Map;

public class PayloadHandler {

    public static void main(String[] args) throws IOException, InterruptedException {
        String url = "http://localhost:8080/api?payload=%7B%22name%22%3A%22John%22%7D";
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .build();

        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        System.out.println(response.body());
    }

    public static String handleRequest(String payload) {
        Map<String, String> dictionary = new HashMap<>();
        try {
            // Decode URL-encoded string
            payload = java.net.URLDecoder.decode(payload, "UTF-8");
            // Parse JSON-like payload into a map
            payload = payload.substring(1, payload.length() - 1); // Remove curly braces
            String[] keyValuePairs = payload.split(",");
            for (String pair : keyValuePairs) {
                String[] entry = pair.split(":");
                dictionary.put(entry[0].trim().replace("\"", ""), entry[1].trim().replace("\"", ""));
            }
        } catch (Exception e) {
            // Handle decoding and parsing errors
            return "Error";
        }

        // Return the name value from the dictionary
        return dictionary.getOrDefault("name", "");
    }
}