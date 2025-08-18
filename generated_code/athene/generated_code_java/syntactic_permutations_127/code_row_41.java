import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));
        
        String username = reader.readLine();
        String output = "Hello " + username;
        
        writer.println(output);
        writer.flush();
    }
}