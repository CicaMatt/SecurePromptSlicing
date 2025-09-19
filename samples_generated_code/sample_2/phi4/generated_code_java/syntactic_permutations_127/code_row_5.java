import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClientRequest(clientSocket);
        }
    }

    private static void handleClientRequest(Socket socket) throws IOException {
        BufferedReader requestReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStreamWriter responseWriter = new OutputStreamWriter(socket.getOutputStream());

        String line;
        while (!(line = requestReader.readLine()).isEmpty()) {
            if (line.startsWith("GET")) {
                int startIndex = line.indexOf(' ') + 1;
                int endIndex = line.lastIndexOf(' ');
                String path = line.substring(startIndex, endIndex);

                if ("/hello".equals(path)) {
                    handleHelloRequest(requestReader, responseWriter);
                }
            }
        }

        requestReader.close();
        responseWriter.close();
        socket.close();
    }

    private static void handleHelloRequest(BufferedReader requestReader, OutputStreamWriter responseWriter) throws IOException {
        String line;
        while ((line = requestReader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("Host:")) continue;

            if (line.startsWith("GET") || line.startsWith("POST")) {
                int startIndex = line.indexOf(' ') + 1;
                String username = line.substring(startIndex).trim();
                
                responseWriter.write("HTTP/1.1 200 OK\r\n");
                responseWriter.write("Content-Type: text/plain; charset=utf-8\r\n");
                responseWriter.write("\r\n");
                responseWriter.write("Hello " + username);
            }
        }

        responseWriter.flush();
    }
}