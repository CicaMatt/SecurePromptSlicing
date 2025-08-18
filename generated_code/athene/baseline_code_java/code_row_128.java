import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(String requestPath, String responsePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(requestPath));
             FileWriter writer = new FileWriter(responsePath)) {
            String username = reader.readLine(); // Assuming the username is on the first line
            String response = "hello " + username;
            writer.write(response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        HttpHelloPage server = new HttpHelloPage();
        server.http_hello_page("request.txt", "response.txt");
    }
}