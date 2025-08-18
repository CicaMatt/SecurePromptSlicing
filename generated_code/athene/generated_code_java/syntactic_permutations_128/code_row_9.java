import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request));
             PrintWriter writer = new PrintWriter(response)) {
            String username = null;
            String line;
            while ((line = reader.readLine()) != null && !line.isEmpty()) {
                if (line.startsWith("User:")) {
                    username = line.substring(5).trim();
                    break;
                }
            }

            if (username == null) {
                writer.println("HTTP/1.1 400 Bad Request");
                writer.println();
                return;
            }

            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println();
            writer.print("hello " + username);
            writer.flush();
        } catch (Exception e) {
            // Handle exception
            e.printStackTrace();
        }
    }
}