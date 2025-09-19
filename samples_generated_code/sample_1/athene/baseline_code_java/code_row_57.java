import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(String requestPath, String responsePath) {
        try (BufferedReader request = new BufferedReader(new FileReader(requestPath));
             FileWriter response = new FileWriter(responsePath)) {

            String username = request.readLine();
            String responseBody = "Hello " + username;
            response.write("HTTP/1.1 200 OK\r\n");
            response.write("Content-Type: text/plain; charset=UTF-8\r\n");
            response.write("Content-Length: " + responseBody.length() + "\r\n");
            response.write("\r\n"); // End of headers
            response.write(responseBody);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}