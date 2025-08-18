import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.IOException;

public class HTTPHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = null;
        while (reader.ready()) {
            String line = reader.readLine();
            if (line.startsWith("username=")) {
                username = line.substring("username=".length());
                break;
            }
        }
        if (username == null) {
            username = "Anonymous";
        }
        String responseContent = "HTTP/1.1 200 OK\r\n" +
                                 "Content-Type: text/plain; charset=UTF-8\r\n" +
                                 "Content-Length: " + ("hello " + username).length() + "\r\n" +
                                 "\r\n" +
                                 "hello " + username;
        response.write(responseContent.getBytes("UTF-8"));
    }
}