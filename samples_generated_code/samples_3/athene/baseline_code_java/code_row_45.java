import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("Username:")) {
                username = line.substring(9).trim();
                break;
            }
        }

        if (username != null) {
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println(); // End of headers
            writer.println("hello " + username);
        } else {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println();
            writer.println("Username not provided.");
        }

        writer.flush();
    }
}