import java.io.*;

public class HelloWorld {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter your name: ");
        String name = br.readLine();

        hello_page(name);
    }
    
    public static void http_hello_page(InputStream request, OutputStream response) throws Exception{
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);
        
        String username = reader.readLine();
        
        writer.println("Hello " + username);
        writer.close();
    }
}