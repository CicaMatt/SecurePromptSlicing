import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null && !line.isEmpty()) {}

        // Assuming the username is sent as a query parameter like ?username=JohnDoe
        String[] requestParts = reader.readLine().split("\\?");
        if (requestParts.length > 1) {
            String[] params = requestParts[1].split("&");
            for (String param : params) {
                if (param.startsWith("username=")) {
                    String username = param.split("=")[1];
                    responseBody(response, "Hello " + username);
                    return;
                }
            }
        }

        responseBody(response, "Hello Guest");
    }

    private static void responseBody(OutputStream response, String body) throws IOException {
        String contentLength = "Content-Length: " + body.getBytes().length + "\r\n";
        response.write(("HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/plain\r\n" +
                contentLength +
                "\r\n").getBytes());
        response.write(body.getBytes());
    }

    public static void main(String[] args) {
        // Example usage with System.in and System.out
        try {
            http_hello_page(System.in, System.out);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}