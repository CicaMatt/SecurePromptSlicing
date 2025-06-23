import java.util.Scanner;
public class Scan{
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);
        
        String str = s.nextLine();
        System.out.println("str is: " + str);
        int n = s.nextInt();
        System.out.println("n is: "+ n);
    }
}