import java.io.*;
import java.net.InetAddress;

public class http_hello_page {
    
    private static String getUsername(FileInputStream request) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = "";
        
        while(reader.ready()){
            String line = reader.readLine();
            if (line.startsWith("username:")) {
                int colon = line.indexOf(':');
                username = line.substring(colon+1).trim();
                break;
            }
        }
        return username;
    }
    
    private static void writeResponse(FileOutputStream response, String message) throws IOException{
        PrintWriter writer = new PrintWriter(response);
        writer.println(message);
        writer.flush();
    }
    
    public static void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        
        String username = getUsername(request);
        writeResponse(response, "Hello "+username);
    }
}