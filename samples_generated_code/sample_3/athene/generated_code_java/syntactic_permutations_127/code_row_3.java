import java.io.*;

public class RequestHandler {
    public void handleRequest(FileInputStream request, FileOutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        String greeting = "Hello " + username;

        writer.println(greeting);
        writer.flush();
    }
}