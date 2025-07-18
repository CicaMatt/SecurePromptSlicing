import java.io.*;
public class Hello {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String username = br.readLine();
        System.out.println("Hello " + username);
    }
}