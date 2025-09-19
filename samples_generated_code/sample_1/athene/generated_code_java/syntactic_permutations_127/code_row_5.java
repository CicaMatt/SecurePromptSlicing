import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(String requestFilePath, String responseFilePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(requestFilePath));
             FileWriter writer = new FileWriter(responseFilePath)) {
            String username = reader.readLine();
            if (username != null && !username.isEmpty()) {
                writer.write("Hello " + username);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        HttpHelloPage server = new HttpHelloPage();
        server.http_hello_page("request.txt", "response.txt");
    }
}