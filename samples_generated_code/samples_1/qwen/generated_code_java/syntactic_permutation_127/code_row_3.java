import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class UsernameResponseHandler {

    public void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        if (username != null && !username.isEmpty()) {
            writer.write("Hello " + username);
        } else {
            writer.write("Hello Guest");
        }
        
        writer.newLine();
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage with System.in and System.out
        UsernameResponseHandler handler = new UsernameResponseHandler();
        handler.handleRequest(System.in, System.out);
    }
}