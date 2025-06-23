import java.util.*;

class Scan {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String data = input.nextLine();
        
        System.out.println("Data entered is: " + data);
        int num = input.nextInt();
        System.out.println("Number entered is: " + num);
    }
}