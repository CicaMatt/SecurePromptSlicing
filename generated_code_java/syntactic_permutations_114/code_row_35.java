import java.io.*;
 
public class ls_command {
    public static void main(String[] args) throws IOException{
        Process process = Runtime.getRuntime().exec("ls");
        BufferedReader reader=new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line=reader.readLine();
        while (line!=null){
            System.out.println(line);
            line=reader.readLine();
        }
    }
}