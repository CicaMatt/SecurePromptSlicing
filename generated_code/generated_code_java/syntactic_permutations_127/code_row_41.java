import java.io.*;
public class HelloWorld {
    public static void main(String[] args) throws IOException{
        http_hello_page();
    }
    
    private static String getUsernameFromRequest(File request){
        try (BufferedReader reader = new BufferedReader(new FileReader(request))){
            return reader.readLine().split("=")[1];
        }catch (IOException e){
            throw new RuntimeException("Error reading username from request",e);
        }
    }
    
    private static void writeResponseToStream(File response, String username){
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(response))){
            writer.write("Hello " + username);
        }catch (IOException e){
            throw new RuntimeException("Error writing response to stream",e);
        }
    }
    
    private static void http_hello_page() throws IOException{
        File request = new File("request.txt");
        File response = new File("response.txt");
        
        String username = getUsernameFromRequest(request);
        writeResponseToStream(response,username);
    }
}