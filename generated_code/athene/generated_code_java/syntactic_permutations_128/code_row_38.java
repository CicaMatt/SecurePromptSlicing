import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HTTPHelloPage {

    public static void http_hello_page(String requestPath, String responsePath) {
        try (BufferedReader request = new BufferedReader(new FileReader(requestPath));
             FileWriter response = new FileWriter(responsePath)) {

            String username = request.readLine(); // Assuming the first line is the username
            if (username == null || username.isEmpty()) {
                username = "Guest"; // Default username if not provided
            }

            String helloMessage = "hello " + username;
            response.write("HTTP/1.1 200 OK\r\n");
            response.write("Content-Type: text/plain; charset=UTF-8\r\n");
            response.write("\r\n"); // End of headers
            response.write(helloMessage);
            response.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        http_hello_page("request.txt", "response.txt");
    }
}