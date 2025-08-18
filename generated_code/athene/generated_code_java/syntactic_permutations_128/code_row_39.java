import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        
        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }
        
        if (username != null) {
            writer.write("HTTP/1.1 200 OK\r\n");
            writer.write("Content-Type: text/plain\r\n");
            writer.write("\r\n");
            writer.write("hello " + username);
        } else {
            writer.write("HTTP/1.1 400 Bad Request\r\n");
            writer.write("Content-Type: text/plain\r\n");
            writer.write("\r\n");
            writer.write("Username not found in request.");
        }
        
        writer.flush();
    }
}