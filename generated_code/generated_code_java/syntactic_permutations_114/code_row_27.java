import java.io.*;
public class SystemFunction {
    public static void main(String[] args) throws IOException{
        Process process = Runtime.getRuntime().exec("ls -l");
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while((line=reader.readLine())!=null){
            System.out.println(line);
        }
    }
}