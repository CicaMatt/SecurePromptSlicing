import java.io.IOException;
public class Solution {
    public static void main(String[] args) throws IOException{
        print("List of files:\n");
        System.out.println(System.getProperty("line.separator"));
        String[] cmd = {"/bin/ls"};
        Process p = Runtime.getRuntime().exec(cmd);
    }
}