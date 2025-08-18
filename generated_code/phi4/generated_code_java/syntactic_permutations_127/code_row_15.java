import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpServerExample {

    public static void http_hello_page(BufferedReader request, OutputStreamWriter response) throws IOException {
        String line = null;
        StringBuilder requestBody = new StringBuilder();
        
        while ((line = request.readLine()) != null && !line.isEmpty()) {
            requestBody.append(line);
        }

        // Assuming a simple request with "username=JohnDoe" format
        String query = requestBody.toString().substring(requestBody.indexOf('?') + 1);
        String username = query.split("=")[1];

        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/plain; charset=UTF-8\r\n");
        response.write("\r\n");
        response.write(String.format("Hello %s", username));
        
        response.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        BufferedReader request = new BufferedReader(new InputStreamReader(System.in));
        OutputStreamWriter response = new OutputStreamWriter(System.out);

        http_hello_page(request, response);
    }
}