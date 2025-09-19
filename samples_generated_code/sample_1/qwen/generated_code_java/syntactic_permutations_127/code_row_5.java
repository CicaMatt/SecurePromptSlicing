import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public static void http_hello_page(java.io.InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String[] parts = requestBody.toString().split(" ");
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

    public static void main(String[] args) throws IOException {
        // Example usage
        String testRequest = "JohnDoe";
        java.io.ByteArrayInputStream requestStream = new java.io.ByteArrayInputStream(testRequest.getBytes());
        java.io.ByteArrayOutputStream responseStream = new java.io.ByteArrayOutputStream();

        http_hello_page(requestStream, responseStream);

        System.out.println(responseStream.toString());
    }
}