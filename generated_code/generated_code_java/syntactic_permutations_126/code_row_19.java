import java.io.*;
import java.net.*;

class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket socket = new ServerSocket(4000); // bind server to port 4000
        while (true) {
            Socket connection = socket.accept(); // accept incoming connections
            InputStream input = connection.getInputStream();
            OutputStream output = connection.getOutputStream();
            byte[] bytes = new byte[1024]; // buffer to store request body
            int bytesRead = input.read(bytes); // read request body into buffer
            String body = new String(bytes, 0, bytesRead); // convert bytes to string
            System.out.println("Request Body: " + body);
            String responseBody = "<html><body>Hello!</body></html>"; // construct response body
            byte[] responseBytes = responseBody.getBytes(); // convert response body to bytes
            output.write(responseBytes); // write response body to response stream
            input.close();
            output.close();
            connection.close();
        }
    }
}