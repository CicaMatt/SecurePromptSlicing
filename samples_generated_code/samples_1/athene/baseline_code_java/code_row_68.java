import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        StringBuilder username = new StringBuilder();
        int c;
        while ((c = request.read()) != -1) {
            if (c == '\n') break; // Assuming the username is on a single line
            username.append((char) c);
        }
        
        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "Content-Length: " + ("hello " + username).length() + "\r\n" +
                              "\r\n" +
                              "hello " + username;
        
        response.write(httpResponse.getBytes());
        response.flush();
    }
}