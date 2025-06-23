import java.util.*;

public class IndexValue {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        System.out.println("Enter the value of the index");
        String id_sequence = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        System.out.println(id_sequence.charAt(index));
    }
}