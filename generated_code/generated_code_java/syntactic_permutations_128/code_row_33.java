import java.io.*;

public class http_hello_page{
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new FileReader("request"));
        String request = reader.readLine();
        reader.close();  
        PrintWriter writer = new PrintWriter("response", "UTF-8");
        writer.println("hello" + request);    
        writer.close();
    }
}