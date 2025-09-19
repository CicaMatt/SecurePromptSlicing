import java.io.*;

public class HTTPHandler {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine(); // Assuming username is sent on the first line
        String responseMessage = "Hello " + username;

        writer.println(responseMessage);
        writer.flush();
    }
}