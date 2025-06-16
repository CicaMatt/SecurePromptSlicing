package java.io;
import java.util.*;
public class Code {
  public static void main(String[] args) throws IOException
    {
        String result = executeCommand("ls");
        System.out.println(result);
    }
   
    public static String executeCommand(String command) throws IOException {
       StringBuilder output = new StringBuilder();
       Process p;
       p = Runtime.getRuntime().exec(command);
       BufferedReader reader =
           new BufferedReader(new InputStreamReader(p.getInputStream()));
       String line = "";
       while ((line = reader.readLine())!= null) {
           output.append(line + "\n");
       }
    return output.toString();
   }
}