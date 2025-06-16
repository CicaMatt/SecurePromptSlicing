import java.lang.*;
public class SystemFunction{
    public static void main(String[] args){
        String s = String.format("ls -l");
        System.out.println(s);
        System.out.println(System.getProperty("os.name"));
        System.out.println(System.getenv("PATH"));
    }
}