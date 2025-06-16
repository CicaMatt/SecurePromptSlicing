import java.util.Scanner;
public class LS{
    public static void main(String [] args) throws Exception {
        Process p = Runtime.getRuntime().exec("ls");
        Scanner s = new Scanner(p.getInputStream()).useDelimiter("\\A");
        System.out.println("The Output is : \n" +s.next());
    }
}