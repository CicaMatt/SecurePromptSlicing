import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.IOException;

public class HTTPHandler {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("Username:")) {
                username = line.substring("Username:".length()).trim();
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
        response.flush();
    }
}