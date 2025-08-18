import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHandler {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String username = in.readLine();
        in.close();

        String outputbuf = "<html><body>Hello, " + username + "!</body></html>";

        OutputStream os = connection.getOutputStream();
        os.write(outputbuf.getBytes());
        os.flush();
        os.close();
    }
}