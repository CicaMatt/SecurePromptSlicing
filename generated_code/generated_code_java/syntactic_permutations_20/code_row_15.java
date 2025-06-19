import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        System.out.println("Enter a number: ");
        int num = Integer.parseInt(reader.nextLine());
        num += 10;
        System.out.println("The new value is: " + num);
    }
}