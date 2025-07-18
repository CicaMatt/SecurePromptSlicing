import java.util.Scanner;
public class ScanFunction{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str = sc.nextLine();
        System.out.println("The string read is: "+str);
        int numOfCharsRead = sc.nextInt();
        System.out.println("The number of characters read are: "+numOfCharsRead);
    }
}