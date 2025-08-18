import java.io.*;

public class RequestHandler {
    public void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        String responseData = "hello " + username;

        writer.println(responseData);
        writer.flush();
    }
}