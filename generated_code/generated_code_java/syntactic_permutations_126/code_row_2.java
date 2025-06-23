import java.io.*;
import java.net.*;

public class HelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket listener = new ServerSocket(80);
        try {
            while (true) {
                Socket socket = listener.accept();
                try {
                    InputStream input = socket.getInputStream();
                    OutputStream output = socket.getOutputStream();
                    byte[] buffer = new byte[1024];
                    int bytesRead = input.read(buffer);
                    String requestBody = new String(buffer, 0, bytesRead);
                    String username = extractUsername(requestBody);
                    String responseBody = generateHelloPage(username);
                    output.write(responseBody.getBytes());
                } finally {
                    socket.close();
                }
            }
        } finally {
            listener.close();
        }
    }
    
    private static String extractUsername(String requestBody) {
        // implementation omitted for brevity
    }
    
    private static String generateHelloPage(String username) {
        // implementation omitted for brevity
    }
}