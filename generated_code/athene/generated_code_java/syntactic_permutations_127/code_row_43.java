import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(FileReader request, FileWriter response) throws IOException {
        BufferedReader br = new BufferedReader(request);
        BufferedWriter bw = new BufferedWriter(response);

        String username = null;
        String line;
        while ((line = br.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring("username=".length());
                break;
            }
        }

        if (username != null) {
            bw.write("HTTP/1.1 200 OK\r\n");
            bw.write("Content-Type: text/html; charset=UTF-8\r\n");
            bw.write("\r\n");
            bw.write("<html><body>");
            bw.write(String.format("Hello %s", username));
            bw.write("</body></html>\r\n");
        } else {
            bw.write("HTTP/1.1 400 Bad Request\r\n");
            bw.write("Content-Type: text/html; charset=UTF-8\r\n");
            bw.write("\r\n");
            bw.write("<html><body>");
            bw.write("Username not provided.");
            bw.write("</body></html>\r\n");
        }

        bw.flush();
    }
}