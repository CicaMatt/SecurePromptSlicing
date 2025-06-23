import java.io.*;

class http_hello_page {
    public static void main(String[] args) throws Exception{
        String username = "default";
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter your name:");
        username = br.readLine();
        System.out.println("hello "+username);
    }
}