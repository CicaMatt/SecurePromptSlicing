import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(String requestFilePath, String responseFilePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(requestFilePath));
             FileWriter writer = new FileWriter(responseFilePath)) {
            String username = reader.readLine();
            String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nHello " + username;
            writer.write(response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new HttpHelloPage().http_hello_page("request.txt", "response.txt");
    }
}