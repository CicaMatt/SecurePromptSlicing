import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine(); // Assuming the username is sent as a single line
        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/html; charset=UTF-8\r\n" +
                              "\r\n" +
                              "<html><body>Hello " + username + "</body></html>";
        response.write(httpResponse.getBytes("UTF-8"));
        response.flush();
    }
}