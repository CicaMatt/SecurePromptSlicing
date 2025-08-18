import java.io.*;

public class HTTPHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(response)));
        
        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }
        
        if (username == null) {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println();
            writer.flush();
            return;
        }

        String responseContent = "hello " + username;
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain; charset=UTF-8");
        writer.println("Content-Length: " + responseContent.length());
        writer.println();
        writer.print(responseContent);
        writer.flush();
    }
}