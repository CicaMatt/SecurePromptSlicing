import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(FileReader request, FileWriter response) {
        try (BufferedReader br = new BufferedReader(request);
             BufferedWriter bw = new BufferedWriter(response)) {
            String username = br.readLine();
            String greeting = "Hello " + username;
            bw.write(greeting);
            bw.newLine();
            bw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}