import java.io.*;
public class HelloWorld {
    public static void main(String[] args) throws IOException {
        String username = "";
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter your name: ");
        username = br.readLine();
        System.out.println("Hello " + username);
    }
}