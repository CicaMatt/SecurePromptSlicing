import java.io.*;
import java.net.*;
import java.util.*;

class Server {
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(80);
        System.out.println("Listening on port 80...");

        while (true) {
            Socket client = server.accept();
            InputStream input = client.getInputStream();
            OutputStream output = client.getOutputStream();

            byte[] buffer = new byte[1024];
            int length = input.read(buffer);
            String requestBody = new String(buffer, 0, length);

            String username = "";
            if (requestBody != null) {
                String[] lines = requestBody.split("\n");
                for (String line : lines) {
                    if (line.contains("username=")) {
                        username = line.substring(line.indexOf("=") + 1);
                        break;
                    }
                }
            }

            String responseBody = "<html><body>Hello, " + username + "</body></html>";
            byte[] responseBuffer = responseBody.getBytes();

            output.write(responseBuffer);
            output.close();
        }
    }
}