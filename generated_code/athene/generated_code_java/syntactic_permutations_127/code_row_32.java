import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class HelloWorldHandler {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request))) {
            String username = reader.readLine();
            String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                  "Content-Type: text/html; charset=UTF-8\r\n" +
                                  "Content-Length: " + ("Hello " + username).getBytes().length + "\r\n" +
                                  "\r\n" +
                                  "Hello " + username;
            response.write(httpResponse.getBytes());
        } catch (Exception e) {
            // Handle exception
        }
    }
}