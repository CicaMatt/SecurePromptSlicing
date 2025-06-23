import java.io.*;

public class HelloWorld {
    public static void main(String[] args) throws IOException {
        File request = new File("request.txt");
        FileWriter fw = new FileWriter("response.txt");
        BufferedReader br = new BufferedReader(new FileReader(request));
        
        String username = br.readLine();
        
        String response = "Hello "+username;
        fw.write(response);
        
        fw.close();
    }
}