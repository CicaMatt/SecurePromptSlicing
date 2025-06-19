import java.io.*;
import java.net.*;

public class HelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(3000);
        while (true) {
            Socket client = server.accept();
            handleClient(client);
            client.close();
        }
    }

    private static void handleClient(Socket client) throws IOException {
        PrintWriter out = new PrintWriter(client.getOutputStream(), true);
        BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        String username = in.readLine();
        out.println("hello " + username);
    }
}