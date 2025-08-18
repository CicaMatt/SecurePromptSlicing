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
            username = parts[1].trim();
        }

        String responseMessage = "Hello " + username;
        response.write(responseMessage.getBytes());
        response.flush();
    }

    public static void main(String[] args) throws IOException {
        HttpHelloPage handler = new HttpHelloPage();
        InputStream request = new java.io.ByteArrayInputStream("username=JohnDoe".getBytes());
        OutputStream response = new java.io.ByteArrayOutputStream();

        handler.http_hello_page(request, response);

        System.out.println(response.toString());
    }
}