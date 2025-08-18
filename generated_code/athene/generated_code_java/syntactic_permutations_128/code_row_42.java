import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHelloPage {

    public static void http_hello_page(String requestPath, String responsePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(requestPath));
             BufferedWriter writer = new BufferedWriter(new FileWriter(responsePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.startsWith("username=")) {
                    String username = line.substring(line.indexOf('=') + 1);
                    writer.write("hello " + username);
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        http_hello_page("request.txt", "response.txt");
    }
}