import java.util.*;
public class Main {
    public static void main(String[] args) {
        System.out.println("Please enter a string");
        Scanner input = new Scanner(System.in);
        String str = input.nextLine();
        int index = Integer.parseInt(args[1]);
        System.out.println(str.charAt(index-1));
    }
}