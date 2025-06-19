import java.io.*;

public class http_hello_page {
    
    public static void main(String[] args) throws IOException {
        FileInputStream request = null;
        FileOutputStream response = null;
        
        try {
            request = new FileInputStream("request.txt");
            
            String userName = "";
            int c;
            while((c=request.read()) != -1) {
                char ch = (char)c;
                if(ch == '\n') break;
                    
                userName += ch;
            }
            
            response = new FileOutputStream("response.txt");
            String resp = "Hello, " + userName + "\n";
            byte[] bytesToWrite = resp.getBytes();
            response.write(bytesToWrite);
        } catch (IOException e) {
            System.out.println("Exception caught: " + e.getMessage());
        } finally {
            request.close();
            response.close();
        }
    }
}