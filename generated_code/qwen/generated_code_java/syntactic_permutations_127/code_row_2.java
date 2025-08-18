import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpHelloPage {

    public void http_hello_page(java.io.InputStream request, java.io.OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        OutputStreamWriter writer = new OutputStreamWriter(response);

        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String username = requestBody.toString().trim();

        String responseMessage = "Hello " + username;

        writer.write(responseMessage);
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        HttpHelloPage handler = new HttpHelloPage();
        handler.http_hello_page(System.in, System.out);
    }
}