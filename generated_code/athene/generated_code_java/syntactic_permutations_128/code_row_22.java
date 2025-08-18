import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        
        String username = reader.readLine();
        String responseMessage = "hello " + username;
        
        writer.write(responseMessage);
        writer.flush();
    }
}