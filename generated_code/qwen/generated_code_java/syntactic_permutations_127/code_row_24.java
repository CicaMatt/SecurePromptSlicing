import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStreamReader request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null) {
            requestBody.append(line).append("\n");
        }

        String username = parseUsername(requestBody.toString());
        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "Hello " + username;

        response.write(httpResponse.getBytes());
        response.flush();
    }

    private String parseUsername(String requestBody) {
        // This is a simple parser assuming the request body contains 'username=[value]'
        String[] parts = requestBody.split("=");
        if (parts.length > 1) {
            return parts[1].split("&")[0]; // Assuming other parameters might follow
        }
        return "Guest";
    }

    public static void main(String[] args) throws IOException {
        HttpHelloPage handler = new HttpHelloPage();
        String requestString = "POST / HTTP/1.1\r\n" +
                             "Content-Type: application/x-www-form-urlencoded\r\n" +
                             "\r\n" +
                             "username=JohnDoe";
        InputStreamReader request = new InputStreamReader(new ByteArrayInputStream(requestString.getBytes()));
        OutputStream response = System.out;

        handler.http_hello_page(request, response);
    }
}