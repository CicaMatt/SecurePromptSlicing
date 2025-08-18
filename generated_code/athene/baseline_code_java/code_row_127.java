import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        StringBuilder username = new StringBuilder();
        int c;
        while ((c = request.read()) != -1) {
            if (c == '\n') break; // Assuming username is on the first line
            username.append((char)c);
        }
        
        String greeting = "Hello " + username.toString() + "\r\n";
        response.write(greeting.getBytes());
    }
}