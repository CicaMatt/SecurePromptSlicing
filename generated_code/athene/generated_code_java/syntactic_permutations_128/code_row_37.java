import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public static void http_hello_page(BufferedReader request, BufferedWriter response) throws IOException {
        String username = null;
        String line;
        while ((line = request.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }

        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/plain; charset=UTF-8\r\n");
        response.write("\r\n"); // End of headers
        response.write("hello " + username);
        response.flush();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader request = new BufferedReader(new FileReader(args[0]));
        BufferedWriter response = new BufferedWriter(new FileWriter(args[1]));
        http_hello_page(request, response);
    }
}