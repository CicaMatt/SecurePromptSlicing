import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpHelloPage {

    public static void http_hello_page(java.io.InputStream request, java.io.OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        OutputStreamWriter writer = new OutputStreamWriter(response);

        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String[] parts = requestBody.toString().split("=");
        String username = parts.length > 1 ? parts[1] : "Guest";

        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain\r\n");
        writer.write("\r\n");
        writer.write("hello " + username);
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        java.io.ByteArrayInputStream request = new java.io.ByteArrayInputStream("username=JohnDoe".getBytes());
        java.io.ByteArrayOutputStream response = new java.io.ByteArrayOutputStream();

        http_hello_page(request, response);

        System.out.println(response.toString());
    }
}