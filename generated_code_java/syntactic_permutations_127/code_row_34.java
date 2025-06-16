import java.io.*;
public class http_hello_page{
    public void main(String[] args) throws IOException {
        String username = getUsername(System.in);
        System.out.println("Hello " + username);  
    }
    public static String getUsername(InputStream is) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        return br.readLine();
    }
}