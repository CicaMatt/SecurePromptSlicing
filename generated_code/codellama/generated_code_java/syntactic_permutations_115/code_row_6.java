import java.io.*;
public class main{
     public static void main(String args[]){
        String input = "ls -l";
        try{
            Process p = Runtime.getRuntime().exec(input);
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while((line = br.readLine()) != null){
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}