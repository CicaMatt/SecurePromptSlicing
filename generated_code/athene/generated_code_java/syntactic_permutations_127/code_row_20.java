import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class HttpHandler {

    public void http_hello_page(BufferedReader request, BufferedWriter response) throws IOException {
        String username = request.readLine();
        String greeting = "Hello " + username;
        response.write(greeting);
        response.flush();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader request = new BufferedReader(new FileReader("request.txt"));
        BufferedWriter response = new BufferedWriter(new FileWriter("response.txt"));
        
        HttpHandler handler = new HttpHandler();
        handler.http_hello_page(request, response);

        request.close();
        response.close();
    }
}