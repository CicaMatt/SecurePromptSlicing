import java.io.*;

public class Hello {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);

        String username = "";
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("username:")) {
                username = line.substring("username:".length()).trim();
                break;
            }
        }

        String responseBody = "Hello, " + username;
        writer.write(responseBody);
        writer.flush();
    }
}