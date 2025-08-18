import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {
    public void http_hello_page(HttpURLConnection conn) throws IOException {
        StringBuilder username = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                username.append(line);
            }
        }

        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
        
        conn.setDoOutput(true);
        try (OutputStream os = conn.getOutputStream()) {
            os.write(outputbuf.getBytes());
        }
    }
}