import java.io.*;

public class http_hello_page {
    
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(response);
        writer.println("Hello " + username);
    }
}