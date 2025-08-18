import java.io.*;

public class ServerHandler {
    public void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        String greeting = "hello " + username;

        writer.println(greeting);
        writer.flush();
    }
}