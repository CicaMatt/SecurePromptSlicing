import java.io.*;
public class hello_page {
    public static void main(String[] args) throws IOException {
        String inputLine = null;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while ((inputLine = br.readLine()) != null) {
            System.out.println("Hello" + inputLine);
        }
    }
}