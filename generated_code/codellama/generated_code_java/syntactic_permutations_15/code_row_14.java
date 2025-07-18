import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); // getting the index value from user
        
        int[] id_sequence = {2, 5, 10, 17, 34, 56, 89};
        
        System.out.println(id_sequence[n]);
    }
}