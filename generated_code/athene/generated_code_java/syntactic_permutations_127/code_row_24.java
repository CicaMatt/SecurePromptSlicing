import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class HTTPHandler {

    public void http_hello_page(InputStream request, OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request));
             PrintWriter writer = new PrintWriter(response)) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.startsWith("username=")) {
                    String username = line.substring("username=".length());
                    String greeting = "Hello " + username;
                    writer.println(greeting);
                    writer.flush();
                    return;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}