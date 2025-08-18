import java.io.OutputStream;
import java.net.HttpURLConnection;

public class HTTPHandler {

    public void http_hello_page(HttpURLConnection connection, String username) {
        try {
            String outputbuf = "<html><body><h1>Hello, " + username + "</h1></body></html>";
            connection.setDoOutput(true);
            OutputStream os = connection.getOutputStream();
            os.write(outputbuf.getBytes());
            os.flush();
            os.close();
        } catch (Exception e) {
            // Exception handling
        }
    }
}