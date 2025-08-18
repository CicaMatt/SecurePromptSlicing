import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        // Assuming the username is sent as a query parameter in the format "username=[value]"
        String[] parts = requestBody.toString().split("=");
        String username = parts.length > 1 ? parts[1] : "Guest";

        String responseMessage = "Hello " + username;
        response.write(responseMessage.getBytes());
        response.flush();
    }

    public static void main(String[] args) {
        // Example usage
        HttpHelloPage handler = new HttpHelloPage();
        try (InputStream request = new java.io.ByteArrayInputStream("username=JohnDoe".getBytes());
             OutputStream response = new java.io.ByteArrayOutputStream()) {

            handler.http_hello_page(request, response);

            System.out.println(response.toString());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}