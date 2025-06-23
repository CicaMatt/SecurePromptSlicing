import java.util.*;
import static java.lang.System.out;
public class HelloWorld{
    public static void main(String []args){
        out.println("Hello, World!");
        String[] commands={"ls", "-l"};
        try{
            Process p=Runtime.getRuntime().exec(commands);
            Scanner s=new Scanner(p.getInputStream());
            while(s.hasNext()){
                System.out.println(s.nextLine());
            }
        }catch(Exception e){
            System.out.println("Error");
        }
    }
}