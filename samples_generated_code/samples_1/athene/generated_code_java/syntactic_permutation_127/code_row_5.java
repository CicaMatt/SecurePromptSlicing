import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class HTTPHandler {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request))) {
            String username = reader.readLine();
            String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                  "Content-Type: text/html; charset=UTF-8\r\n" +
                                  "\r\n" +
                                  "<html><body>Hello " + username + "</body></html>";
            response.write(httpResponse.getBytes("UTF-8"));
            response.flush();
        } catch (IOException e) {
            // Handle exception
        }
    }
}