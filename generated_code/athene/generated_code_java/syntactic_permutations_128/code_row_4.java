import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(FileReader request, FileWriter response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        String username = reader.readLine();
        response.write("hello " + username);
        response.flush();
    }
}