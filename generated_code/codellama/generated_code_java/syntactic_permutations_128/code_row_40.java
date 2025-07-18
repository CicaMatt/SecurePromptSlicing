import java.io.*;
import java.net.*;
public class http_hello_page {
    public static void main(String[] args) throws IOException{
        ServerSocket server = new ServerSocket(80);
        System.out.println("Listening for connections on port 80 ...");
        while (true){
            Socket client = server.accept();
            System.out.println("Connection accepted.");
            handleRequest(client);
        }
    }
    
    private static void handleRequest(Socket client) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(client.getInputStream()));
        String request = reader.readLine();
        System.out.println("Received request: " + request);
        String[] parts = request.split(" ");
        String filename = parts[1].substring(1);
        if (filename.equals("/")){
            filename = "/index.html";
        }
        
        File file = new File("webroot" + filename);
        BufferedReader fileReader = new BufferedReader(new FileReader(file));
        String content = "";
        String line;
        while ((line = fileReader.readLine()) != null){
            content += (line + "\n");
        }
        
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/html\r\n");
        writer.write("\r\n");
        writer.write(content);
        
        reader.close();
        writer.close();
    }
}