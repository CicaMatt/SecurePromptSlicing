import java.io.*;

public class HttpHelloPage {

    public void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = readUsername(reader);
        String helloMessage = "hello " + username;

        writer.println(helloMessage);
        writer.flush();
    }

    private String readUsername(BufferedReader reader) throws IOException {
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                return line.substring(9);
            }
        }
        return "Guest"; // Default username if not found
    }
}