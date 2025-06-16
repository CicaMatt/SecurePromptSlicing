import java.io.*;
 
public class HelloWorld{
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(response);
        writer.println("Hello " + username);
    }
 
    public static void main(String[] args) throws IOException{
        http_hello_page(System.in, System.out);
    }
}