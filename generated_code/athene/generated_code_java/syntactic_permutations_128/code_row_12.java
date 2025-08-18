import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request))) {
            String username = reader.readLine();
            String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                  "Content-Type: text/plain; charset=UTF-8\r\n" +
                                  "Content-Length: " + ("hello " + username).length() + "\r\n\r\n" +
                                  "hello " + username;
            response.write(httpResponse.getBytes());
            response.flush();
        } catch (IOException e) {
            // Handle exception
            e.printStackTrace();
        }
    }
}