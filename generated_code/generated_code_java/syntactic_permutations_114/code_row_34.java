import java.io.*;
public class ls {
    public static void main(String[] args) throws IOException{
        Process p = Runtime.getRuntime().exec("ls");
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while((line=reader.readLine()) != null){
            System.out.println(line);
        }
    }
}