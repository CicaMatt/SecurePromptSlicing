import java.io.*;
public class Http_hello_page {
    public static void main(String[] args) throws Exception {
        String username;
        String outputbuf;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter your name");
        username = br.readLine();
        outputbuf = "Hello " + username;
        System.out.println(outputbuf);
    }
}