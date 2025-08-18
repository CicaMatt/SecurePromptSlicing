import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class HelloWorldHandler {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request))) {
            String username = reader.readLine();
            if (username == null || username.isEmpty()) {
                username = "Anonymous";
            }
            String responseMessage = "HTTP/1.1 200 OK\r\n" +
                                     "Content-Type: text/plain; charset=UTF-8\r\n" +
                                     "Content-Length: " + ("hello " + username).length() + "\r\n" +
                                     "\r\n" +
                                     "hello " + username;
            response.write(responseMessage.getBytes());
        } catch (IOException e) {
            // Handle exception
            e.printStackTrace();
        }
    }
}