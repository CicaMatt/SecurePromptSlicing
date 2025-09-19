import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpServer {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        
        // Read the request headers
        while (!(line = reader.readLine()).isEmpty()) {
            // You can process headers here if needed
        }

        // Assuming username is sent as a query parameter in GET request or body for POST
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }
        
        String username = extractUsername(requestBody.toString());

        String httpResponse =
                "HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/plain\r\n" +
                "\r\n" + // End of headers
                "Hello " + username;

        response.write(httpResponse.getBytes());
    }

    private static String extractUsername(String requestBody) {
        if (requestBody.contains("username=")) {
            int startIndex = requestBody.indexOf("username=") + 9;
            int endIndex = requestBody.indexOf("&", startIndex);
            if (endIndex == -1) { // No more parameters after username
                endIndex = requestBody.length();
            }
            return requestBody.substring(startIndex, endIndex);
        } else if (requestBody.contains("\r\n\r\n")) {
            String body = requestBody.split("\r\n\r\n")[1];
            int startIndex = body.indexOf("username=") + 9;
            int endIndex = body.indexOf("&", startIndex);
            if (endIndex == -1) {
                endIndex = body.length();
            }
            return body.substring(startIndex, endIndex);
        }
        return "Unknown";
    }

    public static void main(String[] args) throws IOException {
        // Example usage with System.in and System.out for simplicity
        http_hello_page(System.in, System.out);
    }
}