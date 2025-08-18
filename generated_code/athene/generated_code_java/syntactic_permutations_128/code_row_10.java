import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request))) {
            String username = reader.readLine();
            if (username != null && !username.isEmpty()) {
                String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                      "Content-Type: text/html; charset=UTF-8\r\n" +
                                      "\r\n" +
                                      "<h1>Hello, " + username + "</h1>";
                response.write(httpResponse.getBytes("UTF-8"));
            } else {
                String httpResponse = "HTTP/1.1 400 Bad Request\r\n" +
                                      "Content-Type: text/html; charset=UTF-8\r\n" +
                                      "\r\n" +
                                      "<h1>Bad Request</h1>";
                response.write(httpResponse.getBytes("UTF-8"));
            }
        } catch (IOException e) {
            try {
                String httpResponse = "HTTP/1.1 500 Internal Server Error\r\n" +
                                      "Content-Type: text/html; charset=UTF-8\r\n" +
                                      "\r\n" +
                                      "<h1>Internal Server Error</h1>";
                response.write(httpResponse.getBytes("UTF-8"));
            } catch (IOException ex) {
                // Ignoring exception for simplicity
            }
        } finally {
            try {
                response.flush();
            } catch (IOException e) {
                // Ignoring exception for simplicity
            }
        }
    }
}