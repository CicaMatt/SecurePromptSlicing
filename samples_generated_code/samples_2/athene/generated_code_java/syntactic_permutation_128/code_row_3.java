import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(BufferedReader request, FileWriter response) throws IOException {
        String username = null;
        String line;
        while ((line = request.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }
        if (username == null) {
            username = "Anonymous";
        }
        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/plain; charset=UTF-8\r\n");
        response.write("\r\n");
        response.write("hello " + username);
        response.flush();
    }

    public static void main(String[] args) {
        try (BufferedReader request = new BufferedReader(new FileReader("request.txt"));
             FileWriter response = new FileWriter("response.txt")) {
            new HttpHelloPage().http_hello_page(request, response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}