import java.io.*;
public class HelloWorld {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(new FileOutputStream("response"));
        writer.println("Hello " + username);
        writer.close();
    }
}