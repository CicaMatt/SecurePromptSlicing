import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPageHandler {
    public void http_hello_page(HttpURLConnection connection) throws IOException {
        StringBuilder inputBuffer = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            inputBuffer.append(line);
        }
        reader.close();

        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, World!</h1>");
        outputbuf.append("</body></html>");

        connection.setDoOutput(true);
        OutputStream os = connection.getOutputStream();
        os.write(outputbuf.toString().getBytes());
        os.close();
    }
}