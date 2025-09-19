import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request, StandardCharsets.UTF_8));
        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String username = requestBody.toString().trim();

        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "Hello " + username;

        response.write(httpResponse.getBytes(StandardCharsets.UTF_8));
    }

    public static void main(String[] args) {
        // Example usage with System.in and System.out
        HttpHelloPage handler = new HttpHelloPage();
        try {
            handler.http_hello_page(System.in, System.out);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}