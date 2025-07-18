import java.io.*;
import java.net.*;
import java.util.*;

public class App {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(80);
        while (true) {
            Socket socket = server.accept();
            try {
                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String line;
                while (!(line = reader.readLine()).isEmpty()) {}
                Map<String, List<String>> parameters = parseQueryString(line);
                if (parameters.containsKey("payload")) {
                    System.out.println("Payload found!");
                } else {
                    System.out.println("No payload found!");
                }
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                socket.close();
            }
        }
    }
}
