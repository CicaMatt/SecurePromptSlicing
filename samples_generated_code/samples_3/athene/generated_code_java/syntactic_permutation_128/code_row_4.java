import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring("username=".length());
                break;
            }
        }

        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain; charset=UTF-8");
        writer.println();
        if (username != null) {
            writer.printf("hello %s", username);
        } else {
            writer.println("hello anonymous");
        }
        writer.flush();
    }
}