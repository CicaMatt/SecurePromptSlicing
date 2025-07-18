import java.io.*;
public class ExecuteCommand{
    public static void main(String[] args){
        try{
            String s= "ls -l";
            Process p = Runtime.getRuntime().exec(s);
            BufferedReader stdInput = new BufferedReader(new  InputStreamReader(p.getInputStream()));
            System.out.println("Here is the standard output of the command:\n");
            String s1 = null;
            while ((s1 = stdInput.readLine()) != null) {
                System.out.println(s1);
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}