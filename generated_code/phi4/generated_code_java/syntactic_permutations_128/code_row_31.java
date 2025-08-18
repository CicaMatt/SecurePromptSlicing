import java.io.*;

public class HttpHelloPage {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String line;
        String username = null;

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET") || line.startsWith("POST")) {
                int startIndex = line.indexOf(" ") + 1;
                int endIndex = line.indexOf(" ", startIndex);
                if (endIndex != -1) {
                    username = line.substring(startIndex, endIndex).trim();
                }
            }
        }

        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
        writer.write("\r\n");

        if (username != null) {
            writer.write("Hello " + username);
        } else {
            writer.write("Hello, unknown user!");
        }

        writer.flush();
    }
}