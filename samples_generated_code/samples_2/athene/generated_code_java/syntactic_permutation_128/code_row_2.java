import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(FileReader request, FileWriter response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring("username=".length());
                break;
            }
        }
        if (username == null) {
            username = "Guest";
        }
        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/plain; charset=UTF-8\r\n");
        response.write("\r\n");
        response.write("hello " + username);
        response.flush();
    }
}