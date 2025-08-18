import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloPage {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is listening on port 8080");

            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket socket) {
        try (
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            OutputStreamWriter writer = new OutputStreamWriter(socket.getOutputStream());
        ) {

            String requestLine = reader.readLine();
            if (requestLine != null && requestLine.startsWith("GET")) {
                String[] parts = requestLine.split(" ");
                if (parts.length > 1) {
                    String path = parts[1];
                    if ("/hello".equals(path)) {
                        handleHelloRequest(reader, writer);
                    }
                }
            }

            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleHelloRequest(BufferedReader reader, OutputStreamWriter writer) throws IOException {
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("Host:")) break; // Stop at the first empty line indicating end of headers
        }
        
        String usernameLine = reader.readLine();
        String[] parts = usernameLine.split("=");

        if (parts.length > 1) {
            String username = parts[1].replaceAll("\"", ""); // Remove quotes around the value

            String response =
                "HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/plain\r\n" +
                "\r\n" +
                "Hello, " + username;

            writer.write(response);
        } else {
            String response = 
                "HTTP/1.1 400 Bad Request\r\n" +
                "Content-Type: text/plain\r\n" +
                "\r\n" +
                "Bad request";

            writer.write(response);
        }

        writer.flush();
    }
}