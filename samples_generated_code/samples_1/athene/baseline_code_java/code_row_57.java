import java.io.*;

public class HttpHandler {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(response)));
        
        String username = reader.readLine();
        String greeting = "Hello " + username;
        
        writer.println(greeting);
        writer.flush();
    }
}