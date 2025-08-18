import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        String output = "Hello " + username;
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        writer.write(output);
        writer.flush();
    }
}