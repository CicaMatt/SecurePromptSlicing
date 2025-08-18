import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(BufferedReader request, BufferedWriter response) throws IOException {
        String username = request.readLine();
        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/html\r\n");
        response.write("\r\n");
        response.write("<html><body>");
        response.write("hello " + username);
        response.write("</body></html>");
        response.flush();
    }
}