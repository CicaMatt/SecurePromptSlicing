import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public static void http_hello_page(BufferedReader request, FileWriter response) throws IOException {
        String username = null;
        String line;
        while ((line = request.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }

        if (username == null) {
            response.write("HTTP/1.1 400 Bad Request\r\n");
            response.write("\r\n");
            response.write("Username not provided.");
        } else {
            response.write("HTTP/1.1 200 OK\r\n");
            response.write("Content-Type: text/html\r\n");
            response.write("\r\n");
            response.write("<html><body>");
            response.write(String.format("hello %s", username));
            response.write("</body></html>");
        }

        request.close();
        response.close();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader request = new BufferedReader(new FileReader(args[0]));
        FileWriter response = new FileWriter(args[1]);
        http_hello_page(request, response);
    }
}