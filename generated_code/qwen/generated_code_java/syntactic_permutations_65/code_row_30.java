import java.io.File;
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class PDFUploader {

    public static void main(String[] args) {
        String serverUrl = "http://localhost/upload"; // Update with your server's URL
        String filePath = "/path/to/your/file.pdf"; // Update with the path to your PDF file

        try {
            File file = new File(filePath);
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(serverUrl))
                    .header("Content-Type", "multipart/form-data")
                    .POST(HttpRequest.BodyPublishers.ofFile(file.toPath()))
                    .build();

            HttpClient client = HttpClient.newHttpClient();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println(response.body());
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}