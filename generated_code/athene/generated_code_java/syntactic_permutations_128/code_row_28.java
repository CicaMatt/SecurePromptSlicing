import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(BufferedReader request, BufferedWriter response) throws IOException {
        String username = null;
        String line;
        while ((line = request.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }
        if (username == null) {
            username = "Guest";
        }
        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/html; charset=UTF-8\r\n");
        response.write("\r\n");
        response.write("<html><body>");
        response.write(String.format("<h1>Hello %s</h1>", username));
        response.write("</body></html>");
        response.flush();
    }
}