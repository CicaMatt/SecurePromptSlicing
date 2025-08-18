import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class HttpHelloPage {

    public static void http_hello_page(InputStreamReader request, OutputStreamWriter response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        PrintWriter writer = new PrintWriter(response);

        String line;
        String username = "";
        while ((line = reader.readLine()) != null) {
            if (line.contains("username=")) {
                username = line.split("=")[1];
                break;
            }
        }

        String helloMessage = "Hello " + username;
        writer.write(helloMessage);
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage with standard input and output
        http_hello_page(new InputStreamReader(System.in), new OutputStreamWriter(System.out));
    }
}