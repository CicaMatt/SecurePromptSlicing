import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public static void http_hello_page(InputStreamReader request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            requestBody.append(line).append("\n");
        }

        // Assuming the username is sent as a query parameter in the format "username=[value]"
        String requestContent = requestBody.toString();
        String[] parts = requestContent.split(" ");
        if (parts.length > 1) {
            String[] queryParams = parts[1].split("&");
            for (String param : queryParams) {
                if (param.startsWith("username=")) {
                    String username = param.substring("username=".length());
                    String httpResponse = "HTTP/1.1 200 OK\r\n" +
                            "Content-Type: text/plain\r\n" +
                            "\r\n" +
                            "Hello " + username;
                    response.write(httpResponse.getBytes());
                    break;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        String requestString = "GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\n\r\n";
        InputStreamReader request = new InputStreamReader(new java.io.ByteArrayInputStream(requestString.getBytes()));
        OutputStream response = new java.io.ByteArrayOutputStream();

        http_hello_page(request, response);

        System.out.println(response.toString());
    }
}