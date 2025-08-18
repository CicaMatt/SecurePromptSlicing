import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is listening on port 8080");

            while (true) {
                try (Socket socket = serverSocket.accept();
                     BufferedReader inputReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                     PrintWriter outputWriter = new PrintWriter(socket.getOutputStream(), true)) {

                    String requestLine = inputReader.readLine();
                    if (requestLine != null && requestLine.contains("GET /hello")) {
                        httpHelloPage(inputReader, outputWriter);
                    } else {
                        outputWriter.println("HTTP/1.1 404 Not Found");
                        outputWriter.println("Content-Type: text/html");
                        outputWriter.println();
                        outputWriter.println("<html><body><h1>Not Found</h1></body></html>");
                    }
                }
            }
        } catch (IOException ex) {
            System.err.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    private static void httpHelloPage(BufferedReader inputReader, PrintWriter outputWriter) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        
        while ((line = inputReader.readLine()) != null && !line.isEmpty()) {
            // Read headers (we are ignoring them here)
        }

        if (inputReader.ready()) {
            String username = inputReader.readLine().trim(); // Assuming the request body is just a single line with the username.
            outputWriter.println("HTTP/1.1 200 OK");
            outputWriter.println("Content-Type: text/html");
            outputWriter.println();
            
            StringBuilder responseBody = new StringBuilder("<html><body>");
            responseBody.append("<h1>Hello, ").append(username).append("</h1>");
            responseBody.append("</body></html>");

            outputWriter.println(responseBody.toString());
        }
    }
}