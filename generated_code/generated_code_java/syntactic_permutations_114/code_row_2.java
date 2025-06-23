import java.lang.*;
public class ls {
    public static void main(String[] args) {
        String cmd = "ls";
        System.out.println("Executing command: " + cmd);
        try{
            Process p = Runtime.getRuntime().exec(cmd);
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}