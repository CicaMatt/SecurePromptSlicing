import java.util.*;
class AddTenHundred {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a number");
        int num = sc.nextInt();
        int total = num + 1000;
        System.out.println("The total is " + total);
    }
}