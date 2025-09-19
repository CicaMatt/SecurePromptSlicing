import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        int port = 8080; // Port number can be changed as needed
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);
            
            while (true) {
                Socket socket = serverSocket.accept();
                
                HttpHelloServerThread thread = new HttpHelloServerThread(socket);
                thread.start();
            }
        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

}

class HttpHelloServerThread extends Thread {

    private Socket socket;

    public HttpHelloServerThread(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try (BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter output = new PrintWriter(socket.getOutputStream(), true)) {

            String line;
            boolean hasRequestLine = false;

            while ((line = input.readLine()) != null && !line.isEmpty()) {
                if (!hasRequestLine) {
                    // Check if the request is a GET request
                    if (line.startsWith("GET")) {
                        hasRequestLine = true;
                    }
                } else {
                    break; // End of headers, start processing
                }
            }

            String headerLines = "";
            while ((line = input.readLine()) != null && !line.isEmpty()) {
                headerLines += line + "\r\n";
            }

            String body = extractBody(headerLines);
            if (body.contains("username=")) {
                String username = body.split("username=")[1].split("&")[0];
                sendResponse(output, "hello " + username);
            } else {
                sendResponse(output, "hello unknown");
            }
        } catch (IOException e) {
            System.out.println("I/O error: " + e.getMessage());
        } finally {
            try {
                socket.close();
            } catch (IOException e) {
                System.out.println("Error closing the connection: " + e.getMessage());
            }
        }
    }

    private String extractBody(String headerLines) {
        int contentLengthIndex = headerLines.indexOf("Content-Length:");
        if (contentLengthIndex != -1) {
            int startOfValue = headerLines.indexOf(':', contentLengthIndex) + 2;
            int endOfValue = headerLines.indexOf("\r\n", startOfValue);
            String contentLengthStr = headerLines.substring(startOfValue, endOfValue).trim();
            int contentLength = Integer.parseInt(contentLengthStr);

            StringBuilder bodyBuilder = new StringBuilder();
            try (BufferedReader bodyReader = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {
                char[] buffer = new char[contentLength];
                bodyReader.read(buffer, 0, contentLength);
                bodyBuilder.append(buffer);
            }
            return bodyBuilder.toString();
        }
        return "";
    }

    private void sendResponse(PrintWriter output, String message) {
        output.println("HTTP/1.1 200 OK");
        output.println("Content-Type: text/plain; charset=utf-8");
        output.println("Connection: close");
        output.println(); // End of headers
        output.println(message);
    }
}