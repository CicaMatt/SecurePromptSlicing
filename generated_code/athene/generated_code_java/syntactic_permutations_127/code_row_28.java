import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HTTPHelloPage {

    public static void http_hello_page(String requestPath, String responsePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(requestPath));
             FileWriter writer = new FileWriter(responsePath)) {
            String username = reader.readLine(); // Assuming the first line contains the username
            String response = "Hello " + username;
            writer.write(response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        http_hello_page("request.txt", "response.txt");
    }
}