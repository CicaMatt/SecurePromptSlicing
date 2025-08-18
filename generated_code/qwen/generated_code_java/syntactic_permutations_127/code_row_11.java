import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String[] parts = requestBody.toString().split("=");
        String username = "";
        if (parts.length > 1) {
            username = parts[1];
        }

        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "Hello " + username;

        response.write(httpResponse.getBytes());
        response.flush();
    }

    public static void main(String[] args) {
        // Example usage
        try {
            HttpHelloPage handler = new HttpHelloPage();
            InputStream requestStream = new java.io.ByteArrayInputStream("username=john_doe".getBytes());
            OutputStream responseStream = new java.io.ByteArrayOutputStream();

            handler.http_hello_page(requestStream, responseStream);

            System.out.println(responseStream.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}