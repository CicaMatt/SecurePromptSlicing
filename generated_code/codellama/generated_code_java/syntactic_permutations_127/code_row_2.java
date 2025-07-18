import java.io.*;

public class HelloPage {
    public static void hello(InputStream inputStream, OutputStream outputStream) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
        String line = "";
        while((line = br.readLine()) != null) {
            if(line.equals("username")) {
                break;
            }
        }
        
        String username = br.readLine();
        
        PrintWriter pw = new PrintWriter(outputStream);
        pw.println("Hello " + username);
    }
}