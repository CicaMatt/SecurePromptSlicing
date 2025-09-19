import java.io.*;

public class ClientHandler {
    public void handleRequest(FileInputStream request, FileOutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        String responseMessage = "Hello " + username;

        writer.println(responseMessage);
        writer.flush();
    }
}