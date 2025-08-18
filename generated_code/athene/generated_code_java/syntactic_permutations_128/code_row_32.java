import java.io.*;

public class ServerHandler {
    public void http__page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring("username=".length());
                break;
            }
        }

        if (username == null) {
            writer.println("Username not found");
        } else {
            writer.println(" Hello, " + username);
        }

        writer.flush();
    }
}